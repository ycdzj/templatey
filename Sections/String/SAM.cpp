struct Node {
	int go[26], par;
	int val;
	void init(int val_) {
		memset(this, 0, sizeof(*this));
		val = val_;
	}
};
struct SAM {
	Node t[MAXN * 2];
	int cnt_node;
	int new_node(int val) {
		t[cnt_node].init(val);
		return cnt_node++;
	}

	int root, last;
	void init() {
		cnt_node = 1;
		root = last = new_node(0);
	}
	void extend(int w) {
		int p = last;
		int np = new_node(t[last].val + 1);
		//t[np].idx = i;
		while(p != 0 && t[p].go[w] == 0) {
			t[p].go[w] = np;
			p = t[p].par;
		}
		if(p == 0) t[np].par = root;
		else {
			int q = t[p].go[w];
			if(t[q].val == t[p].val + 1) t[np].par = q;
			else {
				int nq = new_node(t[p].val + 1);
				memcpy(t[nq].go, t[q].go, sizeof(t[q].go));
				t[nq].par = t[q].par;
				t[q].par = nq;
				t[np].par = nq;
				while(p != 0 && t[p].go[w] == q) {
					t[p].go[w] = nq;
					p = t[p].par;
				}
			}
		}
		last = np;
	}
} sam;