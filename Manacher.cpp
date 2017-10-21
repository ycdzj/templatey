void manacher(char *str, int len, int p[]) {
	p[0] = 1;
	int key = 0;
	for(int i = 1; i < len; i++) {
		int k = (key + p[key] == i) ? 1 : min(key + p[key] - i, p[2 * key - i]);
		while(i - k >= 0 && i + k < len && str[i + k] == str[i - k]) k++;
		p[i] = k;
		if(i + p[i] > key + p[key]) key = i;
	}
}