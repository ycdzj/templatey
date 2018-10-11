//SPOJ  DIVCNTK - Counting Divisors (general)
//Author : Feynman1999   9.27.2018
//f(1)=1
//f(p)=k+1
//f(p^e)=ek+1
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long u64;
u64 n,M,k;
//pre预处理后是2~i的p^0的和  p是素数
//hou是2~n/i的p^0的和
//同理，一个题目可能出现p^1 p^2等需要维护
vector<u64> pre,hou,primes;

// 这里res是n/枚举的数
u64 dfs(u64 res, int last, u64 f){
	//最大质因子是prime[last-1] 但将1放在外面值显然一样
	u64 t=(res > M ? hou[n/res] : pre[res])-pre[primes[last]-1];
	u64 ret= t*f*(k+1);//这里需修改
	for(int i=last;i<(int) primes.size();++i){
		int p = primes[i];
		if((u64)p*p > res) break;
		for(u64 q=p,nres=res,nf=f*(k+1);q*p<=res;q*=p){//nf需修改
			ret += dfs (nres/=p,i+1,nf);//枚举更大的数
			nf += f*k;//继续枚举当前素数，指数大于1时，指数每加1，nf+=f*k  ,k是系数
			ret += nf;//指数大于1时，记上贡献
		}
	}
	return ret;
}
u64 solve(u64 n){
	M=sqrt(n);
	pre.clear();pre.resize(M+1);
	hou.clear();hou.resize(M+1);
	primes.clear();primes.reserve(M+1);
	for(int i=1;i<=M;++i){
		pre[i]=i-1;
		hou[i]=n/i-1;
	}
	for(int p=2;p<=M;++p){
		if(pre[p]==pre[p-1]) continue;
		primes.push_back(p);
		const u64 q=(u64)p*p,m=n/p,pnt=pre[p-1];
		const int mid=M/p;
		const int End=min((u64)M,n/q);
		for(int i=1;i<=mid;++i) hou[i]-=hou[i*p]-pnt;
		for(int i=mid+1;i<=End;++i) hou[i]-=pre[m/i]-pnt;
		for(int i=M;i>=q;--i) pre[i]-=pre[i/p]-pnt;
	}
	primes.push_back(M+1);
	return n>1 ? 1+dfs(n,0,1) : 1;
}
int main()
{
	//freopen("in.txt","r",stdin);
	ios::sync_with_stdio(false);
	int t;
	cin>>t;
	while(t--)
	{
		cin>>n>>k;
		cout<<solve(n)<<endl;
	}
	return 0;
}
