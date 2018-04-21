struct Graph {
	struct { int v, cap, cost, next; } e[MAXM];
	int cntEdge, head[MAXN], nVertex;
	void addEdge_(int u, int v, int cap, int cost) {
		e[cntEdge] = { v, cap, cost, head[u] };
		head[u] = cntEdge++;
	}
	void addEdge(int u, int v, int cap, int cost) {
		addEdge_(u, v, cap, cost);
		addEdge_(v, u, 0, -cost);
	}
	void init(int n) {
		memset(head, 0xff, sizeof(head));
		cntEdge = 0;
		nVertex = n;
	}
	int dis[MAXN], pre[MAXN];
	bool inque[MAXN];
	bool spfa(int s, int t) {
		for(int i = 0; i < nVertex; i++) dis[i] = -inf;
		std::queue<int> q;
		inque[s] = true;
		dis[s] = 0;
		q.push(s);
		while(!q.empty()) {
			int u = q.front(); q.pop();
			inque[u] = false;
			for(int i = head[u]; i != -1; i = e[i].next) if(e[i].cap > 0) {
				if(dis[e[i].v] < dis[u] + e[i].cost) {
					dis[e[i].v] = dis[u] + e[i].cost;
					pre[e[i].v] = i;
					if(!inque[e[i].v]) {
						inque[e[i].v] = true;
						q.push(e[i].v);
					}
				}
			}
		}
		return dis[t] != -inf;
	}
	int maxCostFlow(int s, int t) {
		int res = 0;
		while(spfa(s, t)) {
			int minCap = inf;
			for(int i = t; i != s; i = e[pre[i] ^ 1].v) minCap = std::min(minCap, e[pre[i]].cap);
			for(int i = t; i != s; i = e[pre[i] ^ 1].v) {
				res += e[pre[i]].cost * minCap;
				e[pre[i]].cap -= minCap;
				e[pre[i] ^ 1].cap += minCap;
			}
		}
		return res;
	}
} G;