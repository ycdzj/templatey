//NTT函数，要求n为2的幂次，且n <= MAXN
void ntt(int a[], int n, bool reverse) {
	static int buf[MAXN];
	int lg = 0;
	while((1 << lg) < n) lg++;
	for(int i = 0; i < n; i++) {
		int pos = 0;
		for(int j = 0; j < lg; j++) pos |= ((i >> j & 1) << (lg - 1 - j));
		buf[pos] = a[i];
	}
	for(int i = 0; i < n; i++) a[i] = buf[i];

	for(int l = 1; l < n; l <<= 1) {
		int w = powmod(3, (MOD - 1) / (2 * l));
		if(reverse) w = powmod(w, MOD - 2);
		for(int i = 0; i < n; i += 2 * l) {
			int cur = 1;
			for(int j = 0; j < l; j++) {
				int t = mulmod(cur, a[i + j + l]);
				int u = a[i + j];
				a[i + j] = addmod(u, t);
				a[i + j + l] = addmod(u, MOD - t);
				cur = mulmod(cur, w);
			}
		}
	}
	if(reverse) {
		int inv_n = powmod(n, MOD - 2);
		for(int i = 0; i < n; i++) a[i] = mulmod(a[i], inv_n);
	}
}
void polymul(int res[], int a[], int b[], int n) {
	int m = 1;
	while(m < n) m <<= 1;
	m <<= 1;
	ntt(a, m, false);
	ntt(b, m, false);
	for(int i = 0; i < m; i++) res[i] = mulmod(a[i], b[i]);
	ntt(res, m, true);
}
