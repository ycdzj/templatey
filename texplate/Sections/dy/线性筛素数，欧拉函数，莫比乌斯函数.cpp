//线性筛素数，欧拉函数，莫比乌斯函数
int n,m,k,t,p[maxn],mo[maxn],phi[maxn],cnt;
bool vis[maxn];
void init()
{
    mo[1]=1;
    phi[1]=1;
    for(int i=2;i<=maxn-10;i++)
    {
        if(!vis[i])
        {
            mo[i]=-1;
            phi[i]=i-1;
            p[cnt++]=i;
        }
        for(int j=0;j<cnt&&(ll)i*p[j]<=maxn-10;j++)
        {
            vis[i*p[j]]=true;
            if(i%p[j]==0)
            {
                mo[i*p[j]]=0;
                phi[i*p[j]]=phi[i]*p[j];
                break;
            }
            mo[i*p[j]]=-mo[i];
            phi[i*p[j]]=phi[i]*(p[j]-1);
        }
    }
}