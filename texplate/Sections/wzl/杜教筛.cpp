g(1)S(n)=∑i h(i) - ∑d (2..n) g(d)?S(floor(n/d)

int djsmu(int x)
{
    if(x<=5000000)return sum1[x];
    if(w[x])return w[x];
    int ans=1;
    for(int l=2,r;l<=x;l=r+1)
    {
        r=x/(x/l);
        ans-=(r-l+1)*djsmu(x/l);
    }
    return w[x]=ans;
}
long long djsphi(long long x)
{
    if(x<=5000000)return sum2[x];
    if(w1[x])return w1[x];
    long long ans=x*(x+1)/2;
    for(long long l=2,r;l<=x;l=r+1)
    {
        r=x/(x/l);
        ans-=(r-l+1)*djsphi(x/l);
    }
    return w1[x]=ans;
}
