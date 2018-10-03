//后缀数组
char ch[maxn];
int cntA[maxn],cntB[maxn];
int sa[maxn],lev[maxn],height[maxn];
int A[maxn],B[maxn],tsa[maxn];
void solve(int n,int m)
{
    for (int i = 0; i < m; i ++) cntA[i] = 0;
    for (int i = 1; i <= n; i ++) cntA[ch[i]] ++;
    for (int i = 1; i < m; i ++) cntA[i] += cntA[i - 1];
    for (int i = n; i; i --) sa[cntA[ch[i]] --] = i;
    lev[sa[1]] = 1;
    for (int i = 2; i <= n; i ++)
    {
        lev[sa[i]] = lev[sa[i - 1]];
        if (ch[sa[i]] != ch[sa[i - 1]]) lev[sa[i]] ++;
    }
    for (int l = 1; lev[sa[n]] < n; l <<= 1)
    {
        memset(cntA,0,sizeof(cntA[0])*(n+1));
        memset(cntB,0,sizeof(cntB[0])*(n+1));
        for (int i = 1; i <= n; i ++)
        {
            cntA[A[i] = lev[i]] ++;
            cntB[B[i] = (i + l <= n) ? lev[i + l] : 0] ++;
        }
        for (int i = 1; i <= n; i ++) cntB[i] += cntB[i - 1];
        for (int i = n; i; i --) tsa[cntB[B[i]] --] = i;
        for (int i = 1; i <= n; i ++) cntA[i] += cntA[i - 1];
        for (int i = n; i; i --) sa[cntA[A[tsa[i]]] --] = tsa[i];
        lev[sa[1]] = 1;
        for (int i = 2; i <= n; i ++)
        {
            lev[sa[i]] = lev[sa[i - 1]];
            if (A[sa[i]] != A[sa[i - 1]] || B[sa[i]] != B[sa[i - 1]]) lev[sa[i]] ++;
        }
    }
    for (int i = 1, j = 0; i <= n; i ++)
    {
        if (j) j --;
        while (ch[i + j] == ch[sa[lev[i] - 1] + j]) j ++;
        height[lev[i]] = j;
    }
}