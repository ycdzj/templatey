//链式前向星
bool vis[MAXN];
int link[MAXN];
bool hungarian_dfs(int u) {
	for(int i = head[u]; i != -1; i = e[i].next) if(!vis[e[i].v]) {
		vis[e[i].v] = true;
		if(link[e[i].v] == -1 || hungarian_dfs(link[e[i].v])) {
			link[e[i].v] = u, link[u] = e[i].v;
			return true;
		}
	}
	return false;
}
int hungarian() {
	memset(link, 0xff, sizeof(link));
	int res = 0;
	for(int i = 0; i < n_vertex; i++) if(link[i] == -1) {
		memset(vis, 0, sizeof(vis));
		if(hungarian_dfs(i)) res++;
	}
	return res;
}