import java.util.*;

public class range_SegmentTree {
	public interface BinaryFunction {
		int op(int a, int b);
	}
	public range_SegmentTree(int n, int IDENTITY, BinaryFunction ad, BinaryFunction pw) {
		int[] a = new int[n];
		Arrays.fill(a, IDENTITY);
		init(a, IDENTITY, ad, pw);
	}
	public range_SegmentTree(int[] a, int IDENTITY, BinaryFunction ad, BinaryFunction pw) {
		init(Arrays.copyOf(a, a.length), IDENTITY, ad, pw);
	}
	public int query_range(int l, int r) {
		if(0 <= l && l <= r && r < n) return query_range(h - 1, 0, l, r + 1);
		else return IDENTITY;
	}
	public void update_range(int val, int l, int r) {
		if(0 <= l && l <= r && r < n) update_range(h - 1, 0, l , r + 1, val);
	}

	int IDENTITY;
	BinaryFunction ad, pw;

	int[][] tree, lazy;
	int n, h;

	void init(int[] a, int IDENTITY, BinaryFunction ad, BinaryFunction pw) {
		this.IDENTITY = IDENTITY;
		this.ad = ad;
		this.pw = pw;
		this.n = a.length;

		h = 1;
		for(int t = n; t > 1; t = (t - 1) / 2 + 1) h++;

		tree = new int[h][];
		tree[0] = a;
		for(int i = 1; i < h; i++) {
			tree[i] = new int[(tree[i - 1].length - 1) / 2 + 1];
			for(int j = 0; j < tree[i].length; j++) {
				if(j * 2 + 1 < tree[i - 1].length)
					tree[i][j] = ad.op(tree[i - 1][j * 2], tree[i - 1][j * 2 + 1]);
				else
					tree[i][j] = tree[i - 1][j * 2];
			}
		}

		lazy = new int[h][];
		lazy[0] = new int[n];
		Arrays.fill(lazy[0], IDENTITY);
		for(int i = 1; i < h; i++) lazy[i] = Arrays.copyOf(lazy[0], tree[i].length);
	}
	void update_range(int i, int j, int l, int r, int val) {
		int low = j * (1 << i), high = Math.min(low + (1 << i), n);
		if(l == low && r == high) {
			lazy[i][j] = ad.op(lazy[i][j], val);
			tree[i][j] = ad.op(tree[i][j], pw.op(val, r - l));
		}
		else {
			int mid = Math.min(low + (1 << (i - 1)), n);
			if(r <= mid) update_range(i - 1, j * 2, l, r, val);
			else if(l >= mid) update_range(i - 1, j * 2 + 1, l, r, val);
			else {
				update_range(i - 1, j * 2, l, mid, val);
				update_range(i - 1, j * 2 + 1, mid, r, val);
			}
			if(j * 2 + 1 < tree[i - 1].length) tree[i][j] = ad.op(tree[i - 1][j * 2], tree[i - 1][j * 2 + 1]);
			else tree[i][j] = tree[i - 1][j * 2];
			tree[i][j] = ad.op(tree[i][j], pw.op(lazy[i][j],high - low));
		}
	}
	int query_range(int i, int j, int l, int r) {
		int low = j * (1 << i), high = Math.min(low + (1 << i), n);
		if(l == low && r == high) return tree[i][j];

		int mid = Math.min(low + (1 << (i - 1)), n);
		int res = pw.op(lazy[i][j], r - l);
		if(r <= mid) res = ad.op(res, query_range(i - 1, j * 2, l, r));
		else if(l >= mid) res = ad.op(res, query_range(i - 1, j * 2 + 1, l, r));
		else {
			res = ad.op(res, query_range(i - 1, j * 2, l, mid));
			res = ad.op(res, query_range(i - 1, j * 2 + 1, mid, r));
		}
		return res;
	}

}

