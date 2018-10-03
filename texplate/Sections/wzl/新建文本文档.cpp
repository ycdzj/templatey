int gauss()
{
    int max_r,col,k,i,j;
    for(k=0,col=0;k<equ&&col<var;k++,col++)
    {
        max_r=k;
        for(i=k+1;i<equ;i++)
        {
            if(abs(a[i][col])>abs(a[max_r][col]))
            max_r=i;
        }
        if(a[max_r][col]==0)
        {
            k--;
            continue;
        }
        if(max_r!=k)
        {
            for(j=col;j<=var;j++)
                swap(a[k][j],a[max_r][j]);
        }
        for(i=k+1;i<equ;i++)
        {
            if(a[i][col]!=0)
              {
                 int Lcm=lcm(abs(a[i][col]),abs(a[k][col]));
                 int ta=Lcm/abs(a[i][col]);
                 int tb=Lcm/abs(a[k][col]);
                 if(a[i][col]*a[k][col]<0)
                    tb=-tb;
                 for(j=col;j<=var;j++)
                 {
                     a[i][j]=((a[i][j]*ta-a[k][j]*tb)%mod+mod)%mod;
                 }
              }
        }
    }
    for(i=k;i<equ;i++)
        if(a[i][col]!=0)
        return -1;//无解
    if(k<var)
    return var-k;//多解
    for(i=var-1;i>=0;i--)
    {
        int temp=a[i][var];
        for(j=i+1;j<var;j++)
        {
            if(a[i][j])
            {
                temp-=a[i][j]*x[j];
                temp=(temp%mod+mod)%mod;
            }
        }
        int xx,y;
        exgcd(a[i][i],mod,xx,y);
        x[i]=(temp*xx%mod+mod)%mod;
    }
    return 0;
}
