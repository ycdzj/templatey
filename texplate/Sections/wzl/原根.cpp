void Divide(int n)  {
	for(int i=2; i<=n/i; i++) {
		if(n%i==0) {
			fac[++cnt]=i;
			while(n%i==0)n/=i;
		}
	}
	if(n>1)fac[++cnt]=n;
}
int gete(int p) {
	if(p==2)return 1;int ans=0;
	for(int g=2; g<p; g++) {
		int flag=1;
		for(int i=1; i<=cnt; i++) {
			int t=(p-1)/fac[i];
			if(powmod(g,t,p)==1)  { flag=0;break; }
		}
		if(flag)   ans=g;break;
	}
	return ans;
}
//Divide( phi(n) ); ll g = gete(n);  
