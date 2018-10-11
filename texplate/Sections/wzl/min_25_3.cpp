//SPOJ  DIVCNTK - Counting Divisors (general)
//f(1)=0
//f(p)=p
//f(p^e)=p
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long u64;
u64 n,M;
vector<u64> pre[2],hou[2],primes;
u64 ff(u64 A, u64 B){
	return (A+B)%2?(B-A+1)/2*(A+B):(A+B)/2*(B-A+1);
}
u64 dfs(u64 res, int last, u64 f){
	u64 ret,t;
	if(f>0){
		t = (res > M ? hou[0][n/res] : pre[0][res]) - pre[0][primes[last]-1];//有多少个素数
		//直接-id也行   因为pre[0][primes[last]-1]=id
		ret = t * f * 1;//每个的权值这里就是f
	}
	else ret = hou[1][1];//第一次f=0  计算所有的素数的贡献
	for(int i=last;i<(int) primes.size();++i){
		int p = primes[i];
		if((u64)p*p > res) break;
		for(u64 q=p,nres=res,nf=(f==0?p:f);q*p<=res;q*=p){//f==0表明初始化
			ret += dfs (nres/=p,i+1,nf);
			ret += nf;//f==0 nf就是p  否则就是f
		}
	}
	return ret;
}
u64 solve(u64 n){
	M=sqrt(n);
	for(int i=0;i<2;++i){
		pre[i].clear();pre[i].resize(M+1);
		hou[i].clear();hou[i].resize(M+1);
	}
	primes.clear();primes.reserve(M+1);
	for(int i=1;i<=M;++i){
		pre[0][i]=i-1;
		pre[1][i]=ff(2,i);
		hou[0][i]=n/i-1;
		hou[1][i]=ff(2,n/i);
	}
	for(int p=2;p<=M;++p){
		if(pre[0][p]==pre[0][p-1]) continue;
		primes.push_back(p);
		const u64 q=(u64)p*p,m=n/p,pnt0=pre[0][p-1],pnt1=pre[1][p-1];
		const int mid=M/p;
		const int End=min((u64)M,n/q);
		for(int i=1;i<=mid;++i){
			hou[0][i]-=hou[0][i*p]-pnt0;
			hou[1][i]-=(hou[1][i*p]-pnt1)*p;
		}
		for(int i=mid+1;i<=End;++i){
			hou[0][i]-=pre[0][m/i]-pnt0;
			hou[1][i]-=(pre[1][m/i]-pnt1)*p;
		}
		for(int i=M;i>=q;--i){
			pre[0][i]-=pre[0][i/p]-pnt0;
			pre[1][i]-=(pre[1][i/p]-pnt1)*p;
		}
	}
	primes.push_back(M+1);
	return n>1 ? dfs(n,0,0) : 0;
}