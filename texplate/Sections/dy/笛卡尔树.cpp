//笛卡尔树
void build() {
    int top=0;
    for(int i=1;i<=n;i++)
        l[i]=0,r[i]=0,vis[i]=0;
    for(int i=1;i<=n;i++)
    {
        int k=top;
        while(k>0&&a[stk[k-1]]>a[i])--k;
        if (k) r[stk[k-1]]=i;
        if (k<top) l[i]=stk[k];
        stk[k++]=i;
        top=k;
    }
    for(int i=1;i<=n;i++)
        vis[l[i]]=vis[r[i]]=1;
    int rt=0;
    for(int i=1;i<=n;i++)
        if (vis[i]==0) rt=i;
    dfs(rt);
}
