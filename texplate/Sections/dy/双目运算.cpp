//双目运算
#include <bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
int n,m,k,t;
int ret[maxn];
char a[maxn],b[maxn],c[maxn];
void gao()
{
    int top1=0,top2=0;
    for(int i=0;a[i];i++)
    {
        if(a[i]==' ')continue;
        if(a[i]=='(')c[++top2]=a[i];
        else if(a[i]==')')
        {
            while(c[top2]!='(')b[top1++]=c[top2--];
            top2--;
        }
        else if(a[i]=='|')
        {
            while(top2&&c[top2]!='(')b[top1++]=c[top2--];
            c[++top2]=a[i];
        }
        else if(a[i]=='^')
        {
            while(top2&&c[top2]!='('&&c[top2]!='|')b[top1++]=c[top2--];
            c[++top2]=a[i];
        }
        else if(a[i]=='&')
        {
            while(top2&&c[top2]!='('&&c[top2]!='^'&&c[top2]!='|')b[top1++]=c[top2--];
            c[++top2]=a[i];
        }
        else if(a[i]=='+'||a[i]=='-')
        {
            while(top2&&c[top2]!='('&&c[top2]!='&'&&c[top2]!='^'&&c[top2]!='|')b[top1++]=c[top2--];
            c[++top2]=a[i];
        }
        else if(a[i]=='*'||a[i]=='/')
        {
            while(top2&&c[top2]!='('&&c[top2]!='+'&&c[top2]!='-'&&c[top2]!='&'&&c[top2]!='^'&&c[top2]!='|')b[top1++]=c[top2--];
            c[++top2]=a[i];
        }
        else
        {
            while(a[i]>='0'&&a[i]<='9')b[top1++]=a[i],i++;
            i--;
            b[top1++]='#';
        }
    }
    while(top2)b[top1++]=c[top2--];
    b[top1]=0;
}
int main()
{
    int i,j;
    while(gets(a))
    {
        gao();
        int top=0;
        for(i=0;b[i];i++)
        {
            if(b[i]>='0'&&b[i]<='9')
            {
                int num=0;
                while(b[i]>='0'&&b[i]<='9')num=num*10+b[i]-'0',i++;
                i--;
                ret[++top]=num;
            }
            else if(b[i]=='+')
            {
                ret[top-1]+=ret[top];
                top--;
            }
            else if(b[i]=='-')
            {
                ret[top-1]-=ret[top];
                top--;
            }
            else if(b[i]=='*')
            {
                ret[top-1]*=ret[top];
                top--;
            }
            else if(b[i]=='/')
            {
                ret[top-1]/=ret[top];
                top--;
            }
            else if(b[i]=='&')
            {
                ret[top-1]&=ret[top];
                top--;
            }
            else if(b[i]=='^')
            {
                ret[top-1]^=ret[top];
                top--;
            }
            else if(b[i]=='|')
            {
                ret[top-1]|=ret[top];
                top--;
            }
            else
            {
                continue;
            }
        }
        cout<<ret[1]<<endl;
    }
    return 0;
}