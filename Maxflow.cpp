struct Graph {
	struct {int v, next, c;} e[maxm];
	int head[maxn], cnt_edge, n_vertex;
	void add_edge_(int u, int v, int c) {
		e[cnt_edge].v = v, e[cnt_edge].c = c;
		e[cnt_edge].next = head[u], head[u] = cnt_edge++;
	}
	void add_edge(int u, int v, int c) {
		add_edge_(u, v, c), add_edge_(v, u, 0);
	}
	void init(int n_vertex) {
		this->n_vertex = n_vertex, cnt_edge = 0;
		std::fill(head, head + n_vertex, -1);
	}

	int max_flow_sap(int s, int t) {
		static int d[maxn], gap[maxn], pre[maxn], min_flow[maxn];
		static bool vis[maxn];
		std::fill(vis, vis + n_vertex, false);
		std::fill(d, d + n_vertex, n_vertex);
		std::fill(gap, gap + n_vertex, 0);
		min_flow[s] = inf;

		std::queue<int> q; d[t] = 0, vis[t] = true, q.push(t), gap[d[t]]++;
		while(!q.empty()) {
			int t = q.front(); q.pop();
			for(int i = head[t]; i != -1; i = e[i].next) if(!vis[e[i].v] && e[i ^ 1].c > 0)
				d[e[i].v] = d[t] + 1, vis[e[i].v] = true, q.push(e[i].v), gap[d[t] + 1]++;
		}

		int res = 0;
		for(int u = s; d[s] < n_vertex; ) {
			if(u == t) {
				res += min_flow[t];
				while(u != s) {
					e[pre[u]].c -= min_flow[t];
					e[pre[u] ^ 1].c += min_flow[t];
					u = e[pre[u] ^ 1].v;
				}
			}
			int edg = -1;
			int min_d = n_vertex;
			for(int i = head[u]; i != -1; i = e[i].next) {
				if(e[i].c > 0 && d[e[i].v] + 1 == d[u]) {
					edg = i;
					break;
				}
				if(e[i].c > 0) min_d = std::min(min_d, d[e[i].v]);
			}
			if(edg == -1) {
				if(--gap[d[u]] == 0) break;
				gap[d[u] = min_d + 1]++;
				if(u != s) u = e[pre[u] ^ 1].v;
			}
			else
				min_flow[e[edg].v] = std::min(e[edg].c, min_flow[u]), pre[e[edg].v] = edg, u = e[edg].v;
		}
		return res;
	}
};