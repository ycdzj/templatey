//扩展欧几里得
ll e_gcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0)
    {
        x=1;
        y=0;
        return a;
    }
    ll ans=e_gcd(b,a%b,x,y);
    ll temp=x;
    x=y;
    y=temp-a/b*y;
    return ans;
}
ll cal(ll a,ll b,ll c)//a*x=c(mod b),返回x的最小正整数解,无解返回-1;
{
    ll x,y;
    ll gcd=e_gcd(a,b,x,y);
    if(c%gcd!=0) return -1;
    x*=c/gcd;
    b/=gcd;
    if(b<0) b=-b;
    ll ans=x%b;
    if(ans<=0) ans+=b;
    return ans;
}