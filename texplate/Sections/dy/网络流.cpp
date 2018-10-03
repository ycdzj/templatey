//网络流
struct FLOW
{
    const static int N=20000,M=300000;
    const static int inf=0x3f3f3f3f;
    int h[N],vis[N],cur[N],n,tot,s,t;
    long long flow;
    void init(int n)
    {
        this->n=n;
        tot=0;
        flow=0;
        memset(h,-1,sizeof(h[0])*n);
        memset(cur,0,sizeof(cur[0])*n);
    }
    struct node{int to,nxt,cap,flow;}e[M];
    void link(int x,int y,int z)
    {
        e[tot].to=y;
        e[tot].nxt=h[x];
        e[tot].cap=z;
        e[tot].flow=0;
        h[x]=tot++;
        e[tot].to=x;
        e[tot].nxt=h[y];
        e[tot].cap=0;
        e[tot].flow=0;
        h[y]=tot++;
    }
    bool bfs()
    {
        memset(vis,false,sizeof(vis[0])*n);
        queue<int>p;
        p.push(s);
        vis[s]=1;
        while(!p.empty())
        {
            int x=p.front();p.pop();
            for(int i=h[x];i!=-1;i=e[i].nxt)
            {
                int to=e[i].to,cap=e[i].cap,flow=e[i].flow;
                if(!vis[to]&&cap>flow)
                {
                    vis[to]=vis[x]+1;
                    p.push(to);
                }
            }
        }
        return vis[t];
    }
    int dfs(int x,int a)
    {
        if(x==t||a==0)return a;
        int ans=0,j;
        for(int&i=cur[x];i!=-1;i=e[i].nxt)
        {
            int to=e[i].to,cap=e[i].cap,flow=e[i].flow;
            if(vis[to]==vis[x]+1&&(j=dfs(to,min(a,cap-flow)))>0)
            {
                e[i].flow+=j;
                e[i^1].flow-=j;
                ans+=j;
                a-=j;
                if(a==0)break;
            }
        }
        return ans;
    }
    long long max_flow(int s,int t)
    {
        this->s=s,this->t=t;
        while(bfs())
        {
            memcpy(cur,h,sizeof(h[0])*n);
            flow+=dfs(s,inf);
        }
        return flow;
    }
}mf;