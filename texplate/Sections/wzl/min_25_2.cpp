//phi(1^2)=1
//phi(p^2)=p^2-p
//phi((p^e)^2)=phi((p^{e-1})^2)*p*p;
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=1e9+7;
const int ni6=166666668;
const int ni2=500000004;
ll n,M;
vector<int> pre[3],hou[3],primes;

inline int add(const int x, const int v) {
	return x + v >= mod ? x + v - mod : x + v;
}
inline int dec(const int x, const int v) {
	return x - v < 0 ? x - v + mod : x - v;
}

//这里res是n/枚举的数
int dfs(ll res, int last, ll f){
	//最大质因子是prime[last-1] 但将1放在外面值显然一样
	int t=dec((res > M ? hou[2][n/res] : pre[2][res]),pre[2][primes[last]-1]);
	int ret= (ll)t*f%mod;//这里需修改
	for(int i=last;i<(int) primes.size();++i){
		int p = primes[i];
		if((ll)p*p > res) break;
		const int p2=(ll)p*p%mod;
		for(ll q=p,nres=res,nf=f*p%mod*(p-1)%mod;q*p<=res;q*=p){//nf需修改
			ret = add(ret,dfs(nres/=p,i+1,nf));//枚举更大的数
			nf = nf*p2%mod;//继续枚举当前素数，指数大于1时，指数每加1,nf=nf*p*p;
			ret =add(ret,nf);//指数大于1时，记上贡献
		}
	}
	return ret;
}

inline int ff(ll x){
	x%=mod;
	return x*(x+1)%mod*ni2%mod;
}

inline int fff(ll x){
	x%=mod;
	return x*(x+1)%mod*(2*x+1)%mod*ni6%mod;
}

int solve(ll n){
	M=sqrt(n);
	for(int i=0;i<3;++i){
		pre[i].clear();pre[i].resize(M+1);
		hou[i].clear();hou[i].resize(M+1);
	}
	primes.clear();primes.reserve(M+1);
	for(int i=1;i<=M;++i){
		pre[0][i]=i-1;
		hou[0][i]=n/i-1;
		pre[1][i]=dec(ff(i),1);;
		hou[1][i]=dec(ff(n/i),1);
		pre[2][i]=dec(fff(i),1);
		hou[2][i]=dec(fff(n/i),1);
	}
	for(int p=2;p<=M;++p){
		if(pre[0][p]==pre[0][p-1]) continue;
		primes.push_back(p);
		const ll q=(ll)p*p;
		const int m=n/p,pnt0=pre[0][p-1],pnt1=pre[1][p-1],pnt2=pre[2][p-1];
		const int mid=M/p;
		const int End=min((ll)M,n/q);
		for(int i=1;i<=mid;++i){
			hou[0][i]=dec(hou[0][i],dec(hou[0][i*p],pnt0));
			hou[1][i]=dec(hou[1][i],dec(hou[1][i*p],pnt1)*(ll)p%mod);
			hou[2][i]=dec(hou[2][i],dec(hou[2][i*p],pnt2)*q%mod);
		}
		for(int i=mid+1;i<=End;++i){
			hou[0][i]=dec(hou[0][i],dec(pre[0][m/i],pnt0));
			hou[1][i]=dec(hou[1][i],dec(pre[1][m/i],pnt1)*(ll)p%mod);
			hou[2][i]=dec(hou[2][i],dec(pre[2][m/i],pnt2)*q%mod);
		}
		for(int i=M;i>=q;--i){
			pre[0][i]=dec(pre[0][i],dec(pre[0][i/p],pnt0));
			pre[1][i]=dec(pre[1][i],dec(pre[1][i/p],pnt1)*(ll)p%mod);
			pre[2][i]=dec(pre[2][i],dec(pre[2][i/p],pnt2)*q%mod);
		}
	}
	//cout<<clock()<<endl;
	primes.push_back(M+1);
	for (int i = 1; i <= M; i++) {
		pre[2][i] = dec(pre[2][i], pre[1][i]);//p^p-p
		hou[2][i] = dec(hou[2][i], hou[1][i]);
	}
	return n>1 ? add(dfs(n,0,1),1) : 1;
}

int main()
{
	//freopen("in.txt","r",stdin);
	ios::sync_with_stdio(false);
	cin>>n;
	cout<<1<<endl;
	cout<<solve(n)<<endl;
	return 0;
}