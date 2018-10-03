//虚树
bool cmp(int x,int y){return dfn[x]<dfn[y];}//cmp部分
sort(c+1,c+x+1,cmp);
int top=0;
if(bl[1]!=1)s[++top]=1;
for(i=1;i<=x;i++)
{
    int now=c[i],p=lca(s[top],now);
    while(top>0)
    {
        if(top>1&&dep[p]<dep[s[top-1]])
            add(f,h1,tmp_tot,s[top-1],s[top]),top--;
        else if(dep[p]<dep[s[top]])
            {add(f,h1,tmp_tot,p,s[top]),top--;break;}
        else break;
    }
    if(s[top]!=p)s[++top]=p;
    s[++top]=now;
}