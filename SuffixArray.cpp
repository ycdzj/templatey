struct SuffixArray {
	int pos[maxn], len;
	char* str;
	SegmentTree<int> lcp;

	void build(char* str, int len) {
		static int prm[maxn], count[maxn];
		static bool begin[2][maxn];
		this->len = len;
		this->str = str;

		lcp.init(len, [](int a, int b)->int{return std::min(a, b);});
		for(int i = 0; i < len; i++) pos[i] = i;
		std::sort(pos, pos + len, [&str](int a, int b)->bool { return str[a] < str[b]; });
		for(int i = 0, b = 0; i < len; i++) {
			if(str[pos[b]] != str[pos[i]]) b = i;
			begin[0][i] = b == i;
			lcp[i] = b == i ? 0 : len + 1;
		}
		lcp.build();

		for(int h = 1, bh = 0; h < len; h <<= 1, bh ^= 1) {
			std::fill(count, count + len, 0);
			std::fill(begin[bh ^ 1], begin[bh ^ 1] + len, false);

			for(int i = 0; i < len; i++)
				prm[pos[i]] = begin[bh][i] ? i : prm[pos[i - 1]];
			for(int i = 1; i <= h; i++) {
				prm[len - i] += count[prm[len - i]]++;
				begin[bh ^ 1][prm[len - i]] = true;
			}
			for(int i = 0; i <= len; i++) {
				if(i == len || begin[bh][i]) {
					for(int j = i; j-- > 0; ) {
						if(pos[j] - h >= 0) {
							for(int k = prm[pos[j] - h] + 1; k < len && begin[bh ^ 1][k] && !begin[bh][k]; k++) begin[bh ^ 1][k] = false;
						}
						if(begin[bh][j]) break;
					}
				}
				if(i < len && pos[i] - h >= 0) {
					prm[pos[i] - h] += count[prm[pos[i] - h]]++;
					begin[bh ^ 1][prm[pos[i] - h]] = true;
				}
			}
			for(int i = 0; i < len; i++) pos[prm[i]] = i;
			for(int i = 0; i < len; i++) if(!begin[bh][i] && begin[bh ^ 1][i]) {
					int a = pos[i - 1] + h, b = pos[i] + h, r;
					if(a >= len || b >= len) r = 0;
					else {
						a = prm[a], b = prm[b];
						if(a > b) std::swap(a, b);
						r = lcp.query(a + 1, b);
					}
					lcp.update(i, r + h);
				}
		}
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
