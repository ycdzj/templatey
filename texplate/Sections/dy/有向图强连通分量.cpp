//有向图强连通分量
struct scc
{
    int time,cnt;
    vector<int>dfn,low,scc,sz;
    stack<int>s;
    vector<vector<int> >e;
    void init(int n)
    {
        time=cnt=0;
        dfn.assign(n+1,0);
        low.assign(n+1,0);
        scc.assign(n+1,0);
        sz.assign(n+1,0);
        e.clear();
        e.resize(n+1);
    }
    void add(int x,int y)
    {
        e[x].push_back(y);
    }
    void dfs(int x)
    {
        dfn[x]=low[x]=++time;
        s.push(x);
        for(int i=0;i<e[x].size();i++)
        {
            int y=e[x][i];
            if(!dfn[y])dfs(y),low[x]=min(low[x],low[y]);
            else if(!scc[y])low[x]=min(low[x],dfn[y]);
        }
        if(low[x]==dfn[x])
        {
            ++cnt;
            int y=-1;
            while(y!=x)y=s.top(),s.pop(),scc[y]=cnt,++sz[cnt];
        }
    }
    void find(int n)
    {
        for(int i=1;i<=n;i++)if(!dfn[i])dfs(i);
    }
};