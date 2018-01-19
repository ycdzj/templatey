void getExNext(string &pat, vector<int> &next) {
	int len = pat.length();
	next.resize(len);

	next[0] = len;
	for(int a = 1, p = 1, i = 1; i < len; i++) {
		if(p <= i) a = p = i;

		int k = min(next[i - a], p - i);
		while(i + k < len && pat[i + k] == pat[k]) k++;
		next[i] = k;

		if(i + k > p) p = i + k, a = i;
	}
}
void exKmpMatch(string &s, string &pat, vector<int> &next, vector<int> &lcp) {
	//getExNext(pat, next);
	int len_s = s.length(), len_p = pat.length();
	lcp.resize(len_s);
	for(int a = 0, p = 0, i = 0; i < len_s; i++) {
		if(p <= i) a = p = i;

		int k = min(next[i - a], p - i);
		while(k < len_p && i + k < len_s && pat[k] == s[i + k]) k++;
		lcp[i] = k;

		if(i + k > p) p = i + k, a = i;
	}
}
