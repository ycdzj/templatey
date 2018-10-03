//异或卷积
#define mod 1000000007
#define rev (mod+1)/2
void fwt(int *a,int n)
{
    for(int d=1;d<n;d<<=1)
        for(int m=d<<1,i=0;i<n;i+=m)
            for(int j=0;j<d;j++)
            {
                int x=a[i+j],y=a[i+j+d];
                a[i+j]=(x+y)%mod,a[i+j+d]=(x-y+mod)%mod;
            }
}
void ufwt(int *a,int n)
{
    for(int d=1;d<n;d<<=1)
        for(int m=d<<1,i=0;i<n;i+=m)
            for(int j=0;j<d;j++)
            {
                int x=a[i+j],y=a[i+j+d];
                a[i+j]=1LL*(x+y)*rev%mod,a[i+j+d]=(1LL*(x-y)*rev%mod+mod)%mod;
            }
}
void solve(int *a,int *b,int n)
{
    fwt(a,n);
    fwt(b,n);
    for(int i=0;i<n;i++)a[i]=1LL*a[i]*b[i]%mod;
    ufwt(a,n);
}