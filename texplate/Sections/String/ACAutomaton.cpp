struct ACA {
	struct Node {
		int next[26], fail;
		int end;
		void init() {
			memset(next, 0, sizeof(next));
			fail = end = 0;
		}
	} t[MAXN];
	int cnt_node;
	int new_node() {
		t[cnt_node].init();
		return cnt_node++;
	}

	int root;
	void init() {
		cnt_node = 1;
		root = new_node();
	}
	void insert(char *str, int len) {
		int cur = root;
		for(int i = 0; i < len; i++) {
			if(t[cur].next[str[i] - 'a'] == 0) {
				t[cur].next[str[i] - 'a'] = new_node();
			}
			cur = t[cur].next[str[i] - 'a'];
		}
		t[cur].end++;
	}
	void build() {
		std::queue<int> que;
		t[root].fail = root;
		for(int i = 0; i < 26; i++) {
			if(t[root].next[i] == 0) t[root].next[i] = root;
			else {
				t[t[root].next[i]].fail = root;
				que.push(t[root].next[i]);
			}
		}
		while(!que.empty()) {
			int u = que.front(); que.pop();
			for(int i = 0; i < 26; i++) {
				if(t[u].next[i] == 0) t[u].next[i] = t[t[u].fail].next[i];
				else {
					t[t[u].next[i]].fail = t[t[u].fail].next[i];
					que.push(t[u].next[i]);
				}
			}
		}
	}
} ac;
