struct Graph {
	static const int maxn = 1e4 + 5, maxm = 1e5 + 5;
	struct { int v, next; } e[maxm];
	int head[maxn], cnt_edge;
	void init() {
		memset(head, 0xff, sizeof(head));
		cnt_edge = 0;
	}
	void add_edge(int u, int v) {
		e[cnt_edge].v = v;
		e[cnt_edge].next = head[u], head[u] = cnt_edge++;
	}

	bool cut[maxn], bridge[maxm];
	int bcc_clock, cnt_bcc, cnt_stack, bccno[maxn], dfn[maxn], low[maxn];
	struct { int u, v; } Stack[maxm];
	void bccutil(int u, int pre) {
		dfn[u] = low[u] = ++bcc_clock;
		int cnt_chd = 0;

		for(int i = head[u]; i != -1; i = e[i].next) {
			int v = e[i].v;
			if(dfn[v] == 0) {
				bccutil(v, u);
				cnt_chd++;
				low[u] = std::min(low[u], low[v]);
				Stack[cnt_stack++] = {u, v};
				if(low[v] > dfn[u]) bridge[i] = true;
				if(low[v] >= dfn[u]) {
					cut[u] = true;
					cnt_bcc++;
					while(true) {
						cnt_stack--;
						int cur_u = Stack[cnt_stack].u, cur_v = Stack[cnt_stack].v;
						bccno[cur_u] = bccno[cur_v] = cnt_bcc;
						if(cur_u == u && cur_v == v) break;
					}
				}
			}
			else if(dfn[v] < dfn[u] && v != pre) {
				Stack[cnt_stack++] = {u, v};
				low[u] = std::min(low[u], dfn[v]);
			}
		}
		if(pre == -1 && cnt_chd <= 1) cut[u] = false;
	}
	void bcc(int n) {
		memset(cut, 0, sizeof(cut));
		memset(bridge, 0, sizeof(bridge));
		memset(dfn, 0, sizeof(dfn));
		memset(bccno, 0, sizeof(bccno));
		cnt_stack = bcc_clock = cnt_bcc = 0;

		for(int i = 0; i < n; i++) if(!dfn[i]) bccutil(i, -1);
	}
};
