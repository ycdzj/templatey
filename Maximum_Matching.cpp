struct Graph {
	int head[maxn], cnt_edge, n_vertex;
	struct { int v, next; } e[maxn * maxn];
	void add_edge(int u, int v) {
		e[cnt_edge].v = v;
		e[cnt_edge].next = head[u], head[u] = cnt_edge++;
	}
	void init(int n_vertex) {
		this->n_vertex = n_vertex;
		cnt_edge = 0;
		memset(head, 0xff, sizeof(head));
	}

	bool vis[maxn];
	int link[maxn];
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
		for(int i = 0; i < n_vertex; i++) {
			memset(vis, 0, sizeof(vis));
			if(link[i] == -1 && hungarian_dfs(i)) res++;
		}
		return res;
	}
};