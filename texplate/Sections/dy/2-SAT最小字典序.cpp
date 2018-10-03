//2-SAT最小字典序
int n,m,k,t,head[maxn],S[maxn],tot,top;
bool vis[maxn];
vi pos[maxn];
struct node{
    int to,next;
}e[maxn];
void init() {
    tot = 0;
    memset(head,-1,sizeof(head));
}
void add(int u,int v) {
    e[tot].to = v;
    e[tot].next = head[u];
    head[u] = tot++;
}
bool dfs(int u) {
    if(vis[u^1])return false;
    if(vis[u])return true;
    vis[u] = true;
    S[top++] = u;
    for(int i = head[u]; i != -1; i = e[i].next)
        if(!dfs(e[i].to))
            return false;
    return true;
}
bool Twosat(int n) {
    memset(vis,false,sizeof(vis));
    for(int i = 0; i < n; i += 2) {
        if(vis[i] || vis[i^1])continue;
        top = 0;
        if(!dfs(i)) {
            while(top)vis[S[--top]] = false;
            if(!dfs(i^1)) return false;
        }
    }
    return true;
}