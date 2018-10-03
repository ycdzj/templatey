//凸包
struct Point
{
    int x,y;
    bool operator<(const Point&p)const
    {
        return x<p.x||x==p.x&&y<p.y;
    }
};
struct Hull{
    int n;
    Point P[maxn],S[maxn];
    void make(){
        for(int i=0;i<n;i++)scanf("%d%d",&P[i].x,&P[i].y);
        std::sort(P,P+n);
        int m=0;
        for(int i=0;i<n;i++){
            while(m>1&&1ll*(P[i].y-S[m-1].y)*(S[m-1].x-S[m-2].x)>=1ll*(S[m-1].y-S[m-2].y)*(P[i].x-S[m-1].x))m--;
            S[m++]=P[i];
        }
        int l=m;
        for(int i=n-1;i--;){
            while(m>l&&1ll*(P[i].y-S[m-1].y)*(S[m-1].x-S[m-2].x)>=1ll*(S[m-1].y-S[m-2].y)*(P[i].x-S[m-1].x))m--;
            S[m++]=P[i];
        }
        n=m-1;
    }
}my;