//CRT
void ex_gcd(long long a,long long b,long long &x,long long &y)
{
    if(b==0){x=1;y=0;return;}
    long long x1,y1;
    ex_gcd(b,a%b,x1,y1);
    x=y1;
    y=x1-(a/b)*y1;
}
//求M%A=a,M%B=b,...中的M，其中A,B,C...互质
long long CRT(long long a[],long long m[],int n){
    long long M = 1;
    long long ans = 0;
    for(int i=1; i<=n; i++)
        M *= m[i];
    for(int i=1; i<=n; i++){
        long long x, y;
        long long Mi = M / m[i];
        ex_gcd(Mi, m[i], x, y);
        ans = (ans + Mi * x * a[i]) % M;
    }
    if(ans < 0) ans += M;
    return ans;
}