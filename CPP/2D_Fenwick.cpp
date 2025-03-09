vector bit(n+1,vector<ll>(m+1));
auto add = [&](int x,int y,int d)->void
{
    for (int i=x;i<=n;i+=lowbit(i))
        for (int j=y;j<=m;j+=lowbit(j))
            bit[i][j]+=d;
};
auto query = [&](int x,int y)->ll
{
    ll ret=0;
    for (int i=x;i>0;i-=lowbit(i))
        for (int j=y;j>0;j-=lowbit(j))
            ret+=bit[i][j];
    return ret;
};