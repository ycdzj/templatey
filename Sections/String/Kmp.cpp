void getNext(string &P, int next[]) {
    next[0] = 0;
    for(int pre = 0, i = 1; i < P.length(); i++) {
        while(pre > 0 && P[pre] != P[i]) pre = next[pre - 1];
        if(P[pre] == P[i]) pre++;
        next[i] = pre;
    }
}
void kmpMatch(string &P, string &T, int next[], int kmp[]) {
    for(int pre = 0, i = 0; i < T.length(); i++) {
        while(pre > 0 && P[pre] != T[i]) pre = next[pre - 1];
        if(P[pre] == T[i]) pre++;
        kmp[i] = pre;
        if(pre == P.length()) pre = next[pre - 1];
    }
}
