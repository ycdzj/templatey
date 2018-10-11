#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;

const int M=3e6+10;
const ll p1=469762049ll,p2=998244353ll,p3=1004535809ll,g=3;
const ll Mod=468937312667959297ll;
//三个乘积大于模数且大于最大卷积的系数P*(n-1)^2，原根均为3
int n,m,p;
ll t1[M],t2[M],t3[M],t4[M],ans[3][M];
int R[M];
int fpow(int a,int b,int mod){
	int ans=1;
	for(;b;b>>=1,a=(1ll*a*a)%mod){
		if(b&1) ans=(1ll*ans*a)%mod;
	}
	return ans;
}
ll mul(ll a,ll b,ll mod){
	a%=mod,b%=mod;
	return ((a*b-(ll)((ll)((long double)a/mod*b+1e-3)*mod))%mod+mod)%mod;
}

void DNT(ll *a,int n,int f,int mod){
	for(int i=0;i<n;i++) if(i<R[i]) swap(a[i],a[R[i]]);
	for(int i=2;i<=n;i<<=1){
		int now=i>>1;
		int wn=fpow(g,(mod-1)/i,mod);
		if(f==-1) wn=fpow(wn,mod-2,mod);//逆变换时，逆元，或者采用如下的交换法
		for(int j=0;j<n;j+=i){
			int w=1,x,y;
			for(int k=j;k<j+now;k++,w=1ll*w*wn%mod){
				x=a[k],y=1ll*w*a[k+now]%mod;
				a[k]=(x+y)%mod;a[k+now]=(x-y+mod)%mod;
			}
		}
	}
	if(f==-1){
		int inv=fpow(n,mod-2,mod);
		for(int i=0;i<=n;i++){
			a[i]=1ll*a[i]*inv%mod;
		}
//	  for(int i=1;i<=n/2;i++) swap(a[i],a[n-i]);//交换法，因为g^(-1)=g^(n-1)，所以可以先正变换，翻转就为逆变换。
	}
}

void NTT(ll *a,ll *b,int k,int mod){
	DNT(a,k,1,mod),DNT(b,k,1,mod);
	for(int i=0;i<=k;i++) a[i]=1ll*a[i]*b[i]%mod;
//  DNT(a,k,-1,mod);
}
int k;
void mcpy(int d){
	for(int i=0;i<=k;i++) ans[d][i]=t3[i];
	if(d==2) return;
	memset(t3,0,sizeof(t3));memset(t4,0,sizeof(t4));
	for(int i=0;i<=n;i++) t3[i]=t1[i];
	for(int i=0;i<=m;i++) t4[i]=t2[i];
}

void REV(){
	DNT(ans[0],k,-1,p1);
	DNT(ans[1],k,-1,p2);
	DNT(ans[2],k,-1,p3);
}

int lg;
int main(){
	scanf("%d%d%d",&n,&m,&p);
	for(int i=0;i<=n;i++) scanf("%lld",&t1[i]),t3[i]=t1[i];
	for(int i=0;i<=m;i++) scanf("%lld",&t2[i]),t4[i]=t2[i];
	k=1;while(k<=n+m)k<<=1,++lg;
	for(int i=0;i<k;i++) R[i]=(R[i>>1]>>1)|((i&1)<<(lg-1));
	NTT(t3,t4,k,p1);
	mcpy(0);
	NTT(t3,t4,k,p2);
	mcpy(1);
	NTT(t3,t4,k,p3);
	mcpy(2);
	REV();
	for(int i=0;i<=n+m;i++){//中国剩余定理合并+后面推导出的公式
		ll x=((mul(1ll*ans[0][i]*p2%Mod,fpow(p2%p1,p1-2,p1),Mod))+
			  (mul(1ll*ans[1][i]*p1%Mod,fpow(p1%p2,p2-2,p2),Mod)))%Mod;
		ll y=((((ans[2][i]-x)%p3+p3)%p3)*fpow(Mod%p3,p3-2,p3))%p3;
//	  printf("%lld %lld %lld ",x,y,ans[2][i]);
		printf("%lld ",(1ll*(y%p)*(Mod%p)%p+x%p)%p);
	}
	return 0;
}
