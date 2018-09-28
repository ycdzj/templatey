void mat_mul(int res[][MAXN], int a[][MAXN], int b[][MAXN], int n, int m, int k) {
	static int tmp[MAXN][MAXN];
	for(int i = 0; i < n; i++) for(int j = 0; j < k; j++) {
		long long sum = 0;
		for(int x = 0; x < m; x++) sum += ((long long)a[i][x] * b[x][j]) % MOD;
		tmp[i][j] = sum % MOD;
	}
	for(int i = 0; i < n; i++) for(int j = 0; j < k; j++) res[i][j] = tmp[i][j];
}
void mat_pow(int res[][MAXN], int a[][MAXN], int x, int n) {
	static int cur[MAXN][MAXN];
	for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) cur[i][j] = a[i][j];
	for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) res[i][j] = (i == j) ? 1 : 0;
	while(x) {
		if(x & 1) mat_mul(res, res, cur, n, n, n);
		mat_mul(cur, cur, cur, n, n, n);
		x >>= 1;
	}
}