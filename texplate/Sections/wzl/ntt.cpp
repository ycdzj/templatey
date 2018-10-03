namespace ntt {
    int g = 7, rev[N];
    void dft(int *a, int n, int flag) {
        int k = 0; while((1<<k) < n) k++;
        for(int i=0; i<n; i++) {
            rev[i] = (rev[i>>1]>>1) | ((i&1)<<(k-1));
            if(i < rev[i]) swap(a[i], a[rev[i]]);
        }
        for(int l=2; l<=n; l<<=1) {
            int m = l>>1, wn = Pow(g, flag == 1 ? (P-1)/l : P-1-(P-1)/l);
            for(int *p = a; p != a+n; p += l)
                for(int k=0, w=1; k<m; k++, w = (ll)w*wn %P) {
                    int t = (ll) w * p[k+m] %P, r = p[k];
                    p[k+m] = (r - t + P) %P;
                    p[k] = (r + t) %P;
                }
        }
        if(flag == -1) {
            ll inv = Pow(n, P-2);
            for(int i=0; i<n; i++) a[i] = a[i] * inv %P;
        }
    }
     
    void inverse(int *a, int *b, int l) {
        static int t[N];
        if(l == 1) {b[0] = Pow(a[0], P-2); return;}
        inverse(a, b, l>>1);
        int n = l<<1;
        for(int i=0; i<l; i++) t[i] = a[i], t[i+l] = 0;
        dft(t, n, 1); dft(b, n, 1);
        for(int i=0; i<n; i++) b[i] = (ll) b[i] * (2 - (ll) t[i] * b[i] %P + P) %P;
        dft(b, n, -1); for(int i=l; i<n; i++) b[i] = 0;
    }
 
    void ln(int *a, int *b, int l) {
        static int da[N], ia[N];
        int n = l<<1;
        for(int i=0; i<n; i++) da[i] = ia[i] = 0;
        for(int i=0; i<l-1; i++) da[i] = (ll) (i+1) * a[i+1] %P;
        inverse(a, ia, l);
        dft(da, n, 1); dft(ia, n, 1);
        for(int i=0; i<n; i++) b[i] = (ll) da[i] * ia[i] %P;
        dft(b, n, -1);
        for(int i=l-1; i>0; i--) b[i] = (ll) inv[i] * b[i-1] %P; b[0] = 0;
        for(int i=l; i<n; i++) b[i] = 0;
    }
     
    void exp(int *a, int *b, int l) {
        static int t[N];
        if(l == 1) {b[0] = 1; return;}
        exp(a, b, l>>1);
        int n = l<<1;
        for(int i=0; i<n; i++) t[i] = 0;
        ln(b, t, l);
        for(int i=0; i<l; i++) t[i] = (a[i] - t[i] + P) %P; t[0] = (t[0] + 1) %P;
        dft(b, n, 1); dft(t, n, 1);
        for(int i=0; i<n; i++) b[i] = (ll) b[i] * t[i] %P;
        dft(b, n, -1); for(int i=l; i<n; i++) b[i] = 0;
    }
 
    void power(int *a, int k, int l) {
        static int t[N];
        int n = l<<1;
        for(int i=0; i<n; i++) t[i] = 0;
        ln(a, t, l);
        for(int i=0; i<l; i++) t[i] = (ll) k * t[i] %P;
        for(int i=0; i<n; i++) a[i] = 0;
        exp(t, a, l);
    }
}