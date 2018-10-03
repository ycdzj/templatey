//k是矩阵的秩
int Gauss(int m, int n) {
    int col = 0, k = 0;
    for (; k < m && col < n; ++k, ++col) {
        int r = k;
        for (int i = k + 1; i < m; i++)
            if (fabs(a[i][col]) > fabs(a[r][col])) r = i;
        if (fabs(a[r][col]) < eps) {
            k--;
            continue;
        }
        if (r != k)
            for (int i = 0; i <= n; i++)
                swap(a[k][i], a[r][i]);
        for (int i = k + 1; i < m; i++) {
            double t = a[i][col] / a[k][col];
            for (int j = col; j <= n; j++)a[i][j] -= a[k][j] * t;
            a[i][col] = 0;
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        double tmp = a[i][n];
        for (int j = i + 1; j < n; j++)
            tmp -= x[j] * a[i][j];
        x[i] = (tmp / a[i][i]);
    }
    return 0;
}
 
// 01
void Gauss(bitset<N> a[N], int n) {
    now=1;
    for(int i=1; i<=n; i++) {
        int j=now;
        while(j<=n && !a[j][i]) j++;
        if(j==n+1) continue;
        if(j!=now) swap(a[now], a[j]);
        for(int k=1; k<=n; k++)
            if(k!=now && a[k][i]) a[k]^=a[now];
        now++;
    }
    now--;
}
