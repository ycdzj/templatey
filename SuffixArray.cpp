struct SuffixArray {
	char *str;
	int len;
	int pos[maxn], rank[maxn];
	SegmentTree<int> lcp;

	void build(char *str, int len) {
		this->str = str, this->len = len;
		static bool begin[2][maxn];

		for(int i = 0; i < len; i++) pos[i] = i;
		std::sort(pos, pos + len, [&str](int a, int b)->bool{return str[a] < str[b];});
		for(int i = 0, b = 0; i < len; i++) {
			if(str[pos[i]] != str[pos[b]]) b = i;
			begin[0][i] = begin[1][i] = b == i;
		}

		static int cnt[maxn];
		for(int h = 1, bh = 0; h < len; h <<= 1, bh ^= 1) {
			//stage h:
			std::fill(cnt, cnt + len, 0);
			for(int i = 0; i < len; i++) rank[pos[i]] = begin[bh][i] ? i : rank[pos[i - 1]];

			for(int i = 1; i <= h; i++) {
				rank[len - i] += cnt[rank[len - i]]++;
				begin[bh ^ 1][rank[len - i]] = true;
			}

			for(int i = 0; i <= len; i++) {
				if(i == len || begin[bh][i]) {
					for(int j = i; j-- > 0; ) {
						if(pos[j] >= h) {
							for(int k = rank[pos[j] - h] + 1; k < len && begin[bh ^ 1][k] && !begin[bh][k]; k++) begin[bh ^ 1][k] = false;
						}
						if(begin[bh][j]) break;
					}
				}
				if(i < len && pos[i] >= h) {
					rank[pos[i] - h] += cnt[rank[pos[i] - h]]++;
					begin[bh ^ 1][rank[pos[i] - h]] = true;
				}
			}
			for(int i = 0; i < len; i++) pos[rank[i]] = i;
		}
	}
	void build_lcp() {
		lcp.init(len, [](int a, int b)->int{ return std::min(a, b); });
		for(int i = 0, k = 0; i < len; i++)
			if(rank[i] == 0) k = lcp[rank[i]] = 0;
			else {
				if(k) k--;
				int j = pos[rank[i] - 1];
				while(i + k < len && j + k < len && str[i + k] == str[j + k]) k++;
				lcp[rank[i]] = k;
			}
		lcp.build();
	}
	inline int getLcp(int i, int j) {
		if(i == j) return len - i;
		i = rank[i], j = rank[j];
		if(i > j) std::swap(i, j);
		return lcp.query(i + 1, j);
	}
	int naive_lcp(char* str, int len, char* str_p, int len_p) {
		int t = std::min(len, len_p);
		for(int i = 0; i < t; i++) if(str[i] != str_p[i]) return i;
		return t;
	}
	int lower_bound(char* str_p, int len_p) {
		int L = 0, R = len;
		int p[2] = {naive_lcp(str + pos[L], len - pos[L], str_p, len_p), 0};
		while(L < R) {
			int M = (L + R) / 2;
			int p_[2] = {L == M ? len - pos[M] : lcp.query(L + 1, M), lcp.query(M + 1, R)};
			int d = p[0] < p[1] ? 1 : 0;

			int t;
			if(p[d] == p_[d]) {
				int Min = std::min(len_p, len - pos[M]);
				for(t = p[d]; t < Min && str_p[t] == str[pos[M] + t];) t++;
			}
			else t = std::min(p[d], p_[d]);

			if(str_p[t] <= str[pos[M] + t]) R = M, p[1] = t;
			else if(L == M) L++;
			else L = M, p[0] = t;
		}
		return L;
	}
};
