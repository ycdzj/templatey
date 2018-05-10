class SegmentTree {
	struct Node {
		ll min_, s;
	} tree[maxn * 4];
	void merge(Node &res, Node &l, Node &r) {
		res.min_ = std::min(l.min_ + l.s, r.min_ + r.s);
		res.s = 0;
	}
	void pushDown(Node &root, Node &l, Node &r) {
		root.min_ += root.s;
		l.s += root.s;
		r.s += root.s;
		root.s = 0;
	}
public:
	//root节点对应的线段是[left, right]
	void add(int root, int left, int right, int l, int r, ll d) {
		if(right < l || r < left) return;
		if(l <= left && right <= r) tree[root].s += d;
		else {
			int mid = (left + right) / 2;
			pushDown(tree[root], tree[root << 1], tree[root << 1 | 1]);
			add(root << 1, left, mid, l, r, d);
			add(root << 1 | 1, mid + 1, right, l, r, d);
			merge(tree[root], tree[root << 1], tree[root << 1 | 1]);
		}
	}
	ll queryMin(int root, int left, int right, int l, int r) {
		if(l <= left && right <= r) return tree[root].min_ + tree[root].s;
		else {
			int mid = (left + right) / 2;
			pushDown(tree[root], tree[root << 1], tree[root << 1 | 1]);
			ll L = LONG_LONG_MAX, R = LONG_LONG_MAX;
			if(l <= mid) L = queryMin(root << 1, left, mid, l, r);
			if(mid + 1 <= r) R = queryMin(root << 1 | 1, mid + 1, right, l, r);
			return std::min(L, R);
		}
	}
} sgt;
