ll solve(ll a,ll b,ll c,ll n){  //i=1...n sum floor( (i*a+b)/c )
    ll tmp;
    if (!a) {
        tmp=0;
        return tmp;
    }
    if (a>=c || b>=c){
        tmp=solve(a%c,b%c,c,n);
        n%=mod;
        if (n&1) tmp=(tmp+(n%mod)*((n+1)/2%mod)*(a/c)+(n+1)*(b/c))%mod;
        else tmp=(tmp+(n/2%mod)*((n+1)%mod)*(a/c)+(n+1)*(b/c))%mod;
        return tmp;
    }
    ll m=n/c*a+(n%c*a+b)/c;
    ll nxt=solve(c,c-b-1,a,m-1);
    n%=mod; m%=mod;
    tmp=((n*m-nxt)%mod+mod)%mod;
    //tmp.g=(LL)((n*(n+1)%mo*m-nxt.f-nxt.h)%mo+mo)*inv2%mo;
    //tmp.h=((m*(m+1)%mo*n-(LL)2*(nxt.g+nxt.f)%mo-tmp.f)%mo+mo)%mo;
    return tmp;
}
// g=i*f  ,  h=f*f
data calc(int a,int b,int c,LL n)
{
    data tmp;
    if (!a)
    {
        tmp.f=tmp.g=tmp.h=0;
        return tmp;
    }
    if (a>=c || b>=c)
    {
        tmp=calc(a%c,b%c,c,n);
        n%=mo;
        tmp.h=(tmp.h+n*(n+1)%mo*(2*n+1)%mo*inv6%mo*(a/c)%mo*(a/c)%mo
        +(n+1)*(b/c)%mo*(b/c)%mo
        +(LL)2*(a/c)*tmp.g%mo
        +(LL)2*(b/c)*tmp.f%mo
        +n*(n+1)%mo*(a/c)%mo*(b/c))%mo;
        tmp.f=(tmp.f+n*(n+1)/2%mo*(a/c)+(n+1)*(b/c))%mo;
        tmp.g=(tmp.g+n*(n+1)%mo*(2*n+1)%mo*inv6%mo*(a/c)+n*(n+1)/2%mo*(b/c))%mo;
        return tmp;
    }
    LL m=((LL)a*n+b)/c;
    data nxt=calc(c,c-b-1,a,m-1);
    n%=mo; m%=mo;
    tmp.f=((n*m-nxt.f)%mo+mo)%mo;
    tmp.g=(LL)((n*(n+1)%mo*m-nxt.f-nxt.h)%mo+mo)*inv2%mo;
    tmp.h=((m*(m+1)%mo*n-(LL)2*(nxt.g+nxt.f)%mo-tmp.f)%mo+mo)%mo;
    return tmp;
}