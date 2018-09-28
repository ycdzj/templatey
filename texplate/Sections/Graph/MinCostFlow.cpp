struct Graph {
	struct { int v, cap, cost, next; } e[MAXN * MAXN];
	int cnt_edge, head[MAXN];
	void init() {
		cnt_edge = 0;
		memset(head, 0xff, sizeof(head));
	}
	void add_edge_(int u, int v, int cap, int cost) {
		e[cnt_edge] = { v, cap, cost, head[u] };
		head[u] = cnt_edge++;
	}
	void add_edge(int u, int v, int cap, int cost) {
		add_edge_(u, v, cap, cost);
		add_edge_(v, u, 0, -cost);
	}
	int dis[MAXN], pre[MAXN];
	bool inque[MAXN];
	bool spfa(int s, int t) {
		memset(dis, 0x3f, sizeof(dis));
		std::queue<int> que;
		bool flag = false;

		dis[s] = 0;
		inque[s] = true;
		que.push(s);
		while(!que.empty()) {
			int u = que.front(); que.pop();
			if(u == t) flag = true;
			inque[u] = false;
			for(int i = head[u]; i != -1; i = e[i].next) if(e[i].cap > 0) {
				if(dis[u] + e[i].cost < dis[e[i].v]) {
					dis[e[i].v] = dis[u] + e[i].cost;
					pre[e[i].v] = i;
					if(!inque[e[i].v]) {
						inque[e[i].v] = true;
						que.push(e[i].v);
					}
				}
			}
		}
		return flag;
	}
	int min_cost_flow(int s, int t, int &flow) {
		int cost = 0;
		flow = 0;
		while(spfa(s, t)) {
			int min_cap = 1e9;
			for(int u = t; u != s; u = e[pre[u] ^ 1].v) if(min_cap > e[pre[u]].cap) min_cap = e[pre[u]].cap;
			for(int u = t; u != s; u = e[pre[u] ^ 1].v) {
				cost += min_cap * e[pre[u]].cost;
				e[pre[u]].cap -= min_cap;
				e[pre[u] ^ 1].cap += min_cap;
			}
			flow += min_cap;
		}
		return cost;
	}
} G;