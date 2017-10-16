class ACAutomata {
	static const int maxn = 3e6;
	struct { int v, next; } e[maxn];
	int head[maxn], cnt_e, cnt_v;
	inline void add_edge(int u, int v) {
		e[cnt_e].v = v, e[cnt_e].next = head[u];
		head[u] = cnt_e++;
	}
	char ch[maxn];
	int cnt[maxn], fail[maxn], fail_ocr[maxn];
	inline int add(int root, char c) {
		ch[++cnt_v] = c;
		add_edge(root, cnt_v);
		return cnt_v;
	}
	inline int get_next(int root, char c) {
		for(int i = head[root]; i != -1; i = e[i].next)
			if(ch[e[i].v] == c) return e[i].v;
		return -1;
	}
public:
	void init() {
		memset(head, 0xff, sizeof(head));
		cnt_e = cnt_v = 0;
	}
	void insert(const string &str) {
		int p = 0, len = str.length();
		for(int i = 0; i < len; i++) {
			int next = get_next(p, str[i]);
			if(next == -1) next = add(p, str[i]);
			p = next;
		}
		cnt[p]++;
	}
	void build() {
		queue<int> q;
		q.push(0), fail[0] = 0;
		while(!q.empty()) {
			int u = q.front(); q.pop();
			for(int i = head[u]; i != -1; i = e[i].next) {
				fail[e[i].v] = 0, q.emplace(e[i].v);
				for(int t = fail[u]; t != 0; t = fail[t]) {
					int v = get_next(t, ch[e[i].v]);
					if(v != -1) {
						fail[e[i].v] = v;
						break;
					}
				}
			}
			fail_ocr[u] = cnt[fail[u]] > 0 ? fail[u] : fail_ocr[fail[u]];
		}
	}
};