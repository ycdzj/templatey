void getNext(const string &pat, vector<int> &next) {
    int len = pat.length();
    next.resize(len);
    next[0] = -1;
    for(int j = -1, i = 1; i < len; i++) {
        while(j != -1 && pat[j + 1] != pat[i]) j = next[j];
        if(pat[j + 1] == pat[i]) j++;
        next[i] = j;
    }
}
void kmpMatch(const string &s, const string &pat, const vector<int> &next, vector<int> &kmp) {//untested
	int len_s = s.length(), len_p = pat.length();
	kmp.resize(len_s);
	for(int j = -1, i = 0; i < len_s; i++) {
		while(j != -1 && pat[j + 1] != str[i]) j = next[j];
		if(pat[j + 1] == str[i]) j++;
		kmp[i] = j;
		if(j == len_p - 1) j = next[j];
	}
}