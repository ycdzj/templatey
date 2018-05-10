struct Graph {
	struct { int v, next; } e[maxm];
	int head[maxn], cnt_edge;
	void add_edge(int u, int v) {
		e[cnt_edge] = {v, head[u]};
		head[u] = cnt_edge++;
	}
	void init() {
		memset(head, 0xff, sizeof(head));
		cnt_edge = 0;
	}

	int dfn[maxn], low[maxn], scc_clock;
	int scc_stk[maxn], cnt_stk;
	int sccno[maxn], cnt_scc;

	void scc_dfs(int u) {
		dfn[u] = low[u] = ++scc_clock;
		scc_stk[cnt_stk++] = u;

		for(int i = head[u]; i != -1; i = e[i].next) {
			if(!dfn[e[i].v]) {
				scc_dfs(e[i].v);
				low[u] = std::min(low[u], low[e[i].v]);
			}
			else if(!sccno[e[i].v])
				low[u] = std::min(low[u], dfn[e[i].v]);
		}

		if(low[u] == dfn[u]) {
			cnt_scc++;
			int x;
			do {
				x = scc_stk[--cnt_stk];
				sccno[x] = cnt_scc;
			} while(x != u);
		}
	}
	void find_scc(int n) {
		memset(sccno, 0, sizeof(sccno));
		memset(dfn, 0, sizeof(dfn));
		cnt_stk = cnt_scc = scc_clock = 0;
		for(int i = 0; i < n; i++) if(!dfn[i]) scc_dfs(i);
	}
};