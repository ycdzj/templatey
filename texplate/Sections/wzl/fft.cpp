// fft 多项式A*B |A|=n, |B|=m
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e6+233;
#define DB double
#define pi acos(-1)
 
typedef complex<double> E;
int n,m,L;
int R[maxn];
E a[maxn],b[maxn];
 
inline int read(){
    int  c=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){c=c*10+ch-'0';ch=getchar();}
    return c*f;
}
inline void put(int x)
{
    int num = 0;
    char c[15];
    while(x) c[++num] = (x%10)+48, x /= 10;
    while(num) putchar(c[num--]);
    putchar(' ');
}
 
void fft(E *a,int f)
{
	for(int i=0;i<n;i++)if(i<R[i])swap(a[i],a[R[i]]);
	for(int i=1;i<n;i<<=1)
	{
		E wn(cos(pi/i),f*sin(pi/i));      //当前len=2*i,mid=i;
		for(int p=i<<1,j=0;j<n;j+=p)
		{
			E w(1,0);
			for(int k=0;k<i;k++,w*=wn)     //w(n,k）= cos(2*pi*k/len) + i * sin(2*pi*k/len)  i=sqrt(-1), len=i; 精度高
			{
				E x=a[j+k],y=w*a[j+k+i];
				a[j+k]=x+y;a[j+k+i]=x-y;
			}
		}
	}
}
int main()
{
	n=read();m=read();
	for(int i=0,x;i<=n;i++)x=read(),a[i]=x;
	for(int i=0,x;i<=m;i++)x=read(),b[i]=x;
	m=n+m;for(n=1;n<=m;n<<=1)L++;
	for(int i=0;i<n;i++)R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
	fft(a,1);fft(b,1);
	for(int i=0;i<=n;i++)a[i]=a[i]*b[i];
	fft(a,-1);
	for(int i=0;i<=m;i++)
        //put((int)(a[i].real()/n+0.5));printf(" ");
		printf("%d ",(int)(a[i].real()/n+0.5));
	return 0;
}
