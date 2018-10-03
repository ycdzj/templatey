//NTT
const int G=3;
ll c[maxn],d[maxn],tmp[maxn],wn[maxn];

void getwn(int len)
{
    wn[0]=1;
    wn[1]=qpow(G,(mod-1)/len);
    int i;
    rep(i,2,len) wn[i]=wn[i-1]*wn[1]%mod;
}

void NTT(ll *a,int len,int on){
    int i;
    ll ni=qpow(len,mod-2);
    rep(i,0,len-1){
        int p=0;
        double ce=log(len)/log(2);
        for(int j=0,tp=i;j<ce;j++,tp/=2) p=(p<<1)+(tp%2);
        tmp[p]=a[i];
    }
    for (int m=2;m<=len;m*=2){
        int half=m/2,bei=len/m;
        rep(i,0,half-1){
            ll wi=on>0?wn[i*bei]:wn[len-i*bei];
            for(int j=i;j<len;j+=m){
                ll u=tmp[j],v=tmp[j+half]*wi%mod;
                tmp[j]=(u+v)%mod;
                tmp[j+half]=(u-v+mod)%mod;
            }
        }
    }
    if (on==-1)
        rep(i,0,len-1) tmp[i]=tmp[i]*ni%mod;
    rep(i,0,len-1) a[i]=tmp[i];
}