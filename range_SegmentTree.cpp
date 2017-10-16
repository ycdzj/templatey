template <typename T>
struct range_SegmentTree {
	static const int maxn = 1e6;
	T tree[maxn * 4], lazy[maxn * 4];
	int n;
	std::function<T(T, T)> ad;
	std::function<T(T, int)> pw;
	//T(*ad)(T, T);
	//T(*pw)(T, int);
	void init(const std::function<T(T, T)> &ad, const std::function<T(T, int)> &pw) {
		this->ad = ad, this->pw = pw;
	}
	void build(T* a, int n, T IDENTITY) {
		build(a, 1, 0, n - 1);
		std::fill(lazy, lazy + maxn * 4, IDENTITY);
		this->n = n;
	}
	void update_range(int l, int r, T diff) {
		update_range(1, 0, n - 1, l, r, diff);
	}
	T query_range(int l, int r) {
		return query_range(1, 0, n - 1, l, r);
	}
private:
	void build(T* a, int root, int l, int r) {
		if(l == r) tree[root] = a[l];
		else {
			int mid = (l + r) / 2;
			build(a, root << 1, l, mid);
			build(a, root << 1 | 1, mid + 1, r);
			tree[root] = ad(tree[root << 1], tree[root << 1 | 1]);
		}
	}
	T query_range(int root, int left, int right, int low, int high) {
		T res = pw(lazy[root], high - low + 1);
		if(left == low && right == high) res = ad(res, tree[root]);
		else {
			int mid = (left + right) / 2;
			if(high <= mid) res = ad(res, query_range(root << 1, left, mid, low, high));
			else if(low >= mid + 1) res = ad(res, query_range(root << 1 | 1, mid + 1, right, low, high));
			else {
				T l = query_range(root << 1, left, mid, low, mid);
				T r = query_range(root << 1 | 1, mid + 1, right, mid + 1, high);
				res = ad(res, ad(l, r));
			}
		}
		return res;
	}
	void update_range(int root, int left, int right, int low, int high, T diff) {
		if(left == low && right == high) lazy[root] = ad(lazy[root], diff);
		else {
			int mid = (left + right) / 2;
			if(high <= mid) update_range(root << 1, left, mid, low, high, diff);
			else if(mid + 1 <= low) update_range(root << 1 | 1, mid + 1, right, low, high, diff);
			else {
				update_range(root << 1, left, mid, low, mid);
				update_range(root << 1 | 1, mid + 1, right, mid + 1, high);
			}
			T l = query_range(root << 1, left, mid, left, mid);
			T r = query_range(root << 1 | 1, mid + 1, right, mid + 1, right);
			tree[root] = ad(l, r);
		}
	}
};