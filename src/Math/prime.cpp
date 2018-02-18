void prime(int a[], int n) {
	for(int i = 1; i <= n; i++) a[i] = i;
	for(int i = 2; i * i <= n; i++) if(a[i] == i) {
		for(int j = i * i; j <= n; j += i) a[j] = min(a[j], i);
	}
}
