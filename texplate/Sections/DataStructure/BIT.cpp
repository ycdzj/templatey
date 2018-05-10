template<typename T>
struct BIT {
	static const int maxn = 1e6;
	T tree[maxn];
	int n;//[1, n]
	std::function<T(T, T)> op;
	inline int lowbit(int i) { return i & (-i); }

	void init(int n, const T &ID, const std::function<T(T, T)> &op) {
		this->n = n, this->op = op;
		fill(tree, tree + n + 1, ID);
	}
	T query_prefix(int r) {//[1, r]
		T res = tree[r];
		for(r -= lowbit(r); r > 0; r -= lowbit(r)) res = op(res, tree[r]);
		return res;
	}
	void update(int p, const T &val) {//a[p] = op(a[p], val)
		while(p <= n) tree[p] = op(tree[p], val), p += lowbit(p);
	}
};
