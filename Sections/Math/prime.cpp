bool vis[MAXN];
int pri[MAXN], cnt_pri;
int phi[MAXN];

void prime() {
	phi[1] = 1;
	for(int i = 2; i < MAXN; i++) {
		if(!vis[i]) {
			pri[cnt_pri++] = i;
			phi[i] = i - 1;
		}
		for(int j = 0; j < cnt_pri; j++) {
			if((long long)i * pri[j] >= MAXN) {
				break;
			}
			vis[i * pri[j]] = true;
			if(i % pri[j] != 0) {
				phi[i * pri[j]] = phi[i] * phi[pri[j]];
			}
			else {
				phi[i * pri[j]] = pri[j] * phi[i];
				break;
			}
		}
	}
}
