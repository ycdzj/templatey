struct Graph {
	static const int maxn = 1e4 + 5, maxm = 1e5 + 5;
	struct { int v, next; } e[maxm];
	int head[maxn], cnt_edge;
	void init() {
		memset(head, 0xff, sizeof(head));
		cnt_edge = 0;

		memset(vis, 0, sizeof(vis));
		memset(cut, 0, sizeof(cut));
		memset(bridge, 0, sizeof(bridge));
	}
	void add_edge(int u, int v) {
		e[cnt_edge].v = v;
		e[cnt_edge].next = head[u], head[u] = cnt_edge++;
	}

	bool vis[maxn], cut[maxn], bridge[maxm];
	int d[maxn];
	int dfs(int u, int pre_e, int d_ = 0) {
		vis[u] = true;
		int res = d[u] = d_, cnt_chd = 0;
		bool flag = true;
		for(int i = head[u]; i != -1; i = e[i].next) {
			int v = e[i].v;
			if(!vis[v]) {
				cnt_chd++;
				int t = dfs(v, i, d_ + 1);
				res = std::min(res, t);
				if(t == d_) cut[u] = true;
				else flag = false;
			}
			res = std::min(res, d[v]);
		}
		if(pre_e != -1 && flag && res == d_ - 1) bridge[pre_e] = true;
		if(pre_e == -1) cut[u] = cnt_chd > 1;
		return res;
	}
	//for(int i = 0; i < n; i++) if(!G.vis[i]) G.dfs(i, -1);
};
