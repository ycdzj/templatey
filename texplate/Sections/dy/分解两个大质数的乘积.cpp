//分解两个大质数的乘积
ll qmul(ll p,ll q,ll mo){ll f=0;while(q){if(q&1)f=(f+p)%mo;p=(p+p)%mo;q>>=1;}return f;}
void P_RHO(ll x,ll &p,ll &q) {
    ll a=1,y1,y2,t;
    while(1) {
        y1=y2=rand()%x;
        y1=(qmul(y1,y1,x)+a)%x;
        while(1) {
            if(y1==y2)break;
            t=gcd(y1>y2?y1-y2:y2-y1,x);
            if(t!=1) {
                p=t;
                q=x/t;
                return;
            }
            y2=(qmul(y2,y2,x)+a)%x;
            y1=(qmul(y1,y1,x)+a)%x;
            y1=(qmul(y1,y1,x)+a)%x;
        }
        a++;
    }
}