void calc_z(char *str, int len, int *z) {
	int l = 0, r = 0;
	for(int i = 1; i < len; i++) {
		z[i] = 0;
		if(i <= r) z[i] = std::min(z[i - l], r - i + 1);
		while(i + z[i] < len && str[i + z[i]] == str[z[i]]) z[i]++;
		if(i + z[i] - 1 > r) { l = i; r = i + z[i] - 1; }
	}
}