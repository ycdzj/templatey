struct Graph {
	struct { int v, cap, next; } e[maxm];
	int head[maxn], cnt_edge;
	void add_edge_(int u, int v, int cap) {
		e[cnt_edge] = { v, cap, head[u] };
		head[u] = cnt_edge++;
	}
	void add_edge(int u, int v, int cap) {
		add_edge_(u, v, cap);
		add_edge_(v, u, 0);
	}
	void init() {
		memset(head, 0xff, sizeof(head));
		cnt_edge = 0;
	}
	
	int level[maxn], cur[maxn];
	bool dinic_bfs(int s, int t) {
		memset(level, 0xff, sizeof(level));
		std::queue<int> q;

		level[s] = 0;
		cur[s] = head[s];
		q.push(s);
		while(!q.empty()) {
			int u = q.front(); q.pop();
			if(u == t) return true;
			for(int i = head[u]; i != -1; i = e[i].next) if(e[i].cap) {
				if(level[e[i].v] == -1) {
					level[e[i].v] = level[u] + 1;
					cur[e[i].v] = head[e[i].v];
					q.push(e[i].v);
				}
			}
		}
		return false;
	}

	int dinic_dfs(int u, int cur_min, int t) {
		if(u == t) return cur_min;
		if(level[u] >= level[t]) return 0;

		int res = 0;
		for(int& i = cur[u]; cur_min && i != -1; i = e[i].next) if(e[i].cap) {
			if(level[e[i].v] == level[u] + 1) {
				int nxt_min = std::min(cur_min, e[i].cap);
				int x = dinic_dfs(e[i].v, nxt_min, t);
				cur_min -= x;
				e[i].cap -= x;
				e[i ^ 1].cap += x;
				res += x;
			}
		}
		return res;
	}

	int dinic(int s, int t) {
		int res = 0;
		while(dinic_bfs(s, t)) {
			res += dinic_dfs(s, inf, t);
		}
		return res;
	}
} G;
