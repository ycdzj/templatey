struct Graph {
	struct { int v, next; } e[MAXM];
	int head[MAXN], cnt_edge;
	void add_edge(int u, int v) {
		e[cnt_edge] = { v, head[u] };
		head[u] = cnt_edge++;
	}
	void init() {
		cnt_edge = 0;
		memset(head, 0xff, sizeof(head));
	}
	int dfs_clk, dfn[MAXN];
	bool cut[MAXN], bridge[MAXM];
	int bcc_dfs(int u, int pre) {
		dfn[u] = ++dfs_clk;
		int cnt_child = 0;
		int low_u = dfn[u];
		for(int i = head[u]; i != -1; i = e[i].next) if(e[i].v != pre) {
				int v = e[i].v;
				if(dfn[v] == 0) {
					cnt_child++;
					int low_v = bcc_dfs(v, u);
					if(low_v >= dfn[u]) cut[u] = true;
					if(low_v >= dfn[v]) bridge[i] = bridge[i ^ 1] = true;
					low_u = std::min(low_u, low_v);
				}
				else {
					low_u = std::min(low_u, dfn[v]);
				}
			}
		if(u == pre && cnt_child == 1) cut[u] = false;
		return low_u;
	}
	void calc_bcc() {
		memset(cut, 0, sizeof(cut));
		memset(bridge, 0, sizeof(bridge));
		memset(dfn, 0, sizeof(dfn));
		dfs_clk = 0;
		bcc_dfs(0, 0); //搜索开始的点为0
	}
} G;