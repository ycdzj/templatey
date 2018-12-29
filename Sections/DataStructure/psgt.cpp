struct PSGT {
	struct Node {
		int sum;
		int lc, rc;
	} tree[MAXN * 20];
	int cnt_node;
	int copy_of(int u) {
		tree[cnt_node] = tree[u];
		return cnt_node++;
	}
	void init() {
		cnt_node = 1;
	}
	int build(int l, int r) {
		int root = cnt_node++;
		if(l == r) {
			tree[root].lc = tree[root].rc = -1;
			tree[root].sum = 0;
		}
		else {
			int mid = (l + r) / 2;
			int lc = build(l, mid), rc = build(mid + 1, r);
			tree[root].lc = lc;
			tree[root].rc = rc;
			tree[root].sum = tree[lc].sum + tree[rc].sum;
		}
		return root;
	}
	int query(int root, int left, int right, int l, int r) {
		if(l <= left && right <= r) return tree[root].sum;
		if(r < left || right < l) return 0;
		int mid = (left + right) / 2;
		return query(tree[root].lc, left, mid, l, r) + query(tree[root].rc, mid + 1, right, l, r);
	}
	int modify(int root, int left, int right, int p, int val) {
		int res = copy_of(root);
		if(left == p && right == p) tree[res].sum += val;
		else {
			int mid = (left + right) / 2;
			if(p <= mid) tree[res].lc = modify(tree[root].lc, left, mid, p, val);
			else tree[res].rc = modify(tree[root].rc, mid + 1, right, p, val);
			tree[res].sum = tree[tree[res].lc].sum + tree[tree[res].rc].sum;
		}
		return res;
	}
} psgt;