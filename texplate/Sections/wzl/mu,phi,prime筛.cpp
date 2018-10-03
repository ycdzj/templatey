void init() {
    mu[1]=1,phi[1]=1;
    rep(i,2,maxn) {
        if (!vis[i]) {
            mu[i]=-1,phi[i]=i-1,prime[++tot]=i;
        }
        for(int j=1;j<=tot&&1ll*prime[j]*i<maxn;j++) {
            vis[i*prime[j]]=1;
            if (i%prime[j]==0) {
                mu[i*prime[j]]=0;
                phi[i*prime[j]]=prime[j]*phi[i];
                break;
            }
            mu[i*prime[j]]=-mu[i];
            phi[i*prime[j]]=(prime[j]-1)*phi[i];
        }
    }
    rep(j,1,tot+1) {
        for(int i=1;1ll*i*prime[j]<maxn;i++) g[i*prime[j]]+=mu[i];
    }
    rep(i,1,maxn) sum[i]=sum[i-1]+g[i];
}