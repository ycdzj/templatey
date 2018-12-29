template <typename T>
struct ZKW {
	T tree[MAXN * 2];
	int n;
	void build() {
		for(int p = n - 1; p >= 1; p--) tree[p] = op(tree[p << 1], tree[p << 1 | 1]);
	}
	void update(int p, T val) {//a[p] = val
		tree[p += n] = val;
		for(p >>= 1; p > 0; p >>= 1) tree[p] = op(tree[p << 1], tree[p << 1 | 1]);
	}
	T query(int l, int r) {//[l, r]
		l += n; r += n;
		T res = tree[r];
		for(; l < r; l >>= 1, r >>= 1) {
			if(l & 1) res = op(res, tree[l++]);
			if(r & 1) res = op(res, tree[--r]);
		}
		return res;
	}
};
