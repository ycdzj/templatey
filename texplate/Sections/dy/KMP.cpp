//KMP
int kmp(char *p,char *q)                //p为模板,q为待匹配串;
{
    int n=strlen(p),i,j=-1,ans=0;
    nxt[0]=-1;
    for(i=0;p[i];)
    {
        if(j==-1||p[i]==p[j])nxt[++i]=++j;
        else j=nxt[j];
    }
    j=0;
    for(i=0;q[i];)
    {
        if(j==-1||q[i]==p[j])++i,++j;
        else j=nxt[j];
        if(j==n)ans++;
    }
    return ans;
}