int n,m,e;
cin>>n>>m>>e;
vector<int> vis(m+1),con(m+1);
vector dis(n+1,vector<int>(m+1));
for(int i=1;i<=e;i++)
{
    int u,v;
    cin>>u>>v;
    dis[u][v]=1;
}
auto dfs=[&](auto &&dfs,int x)->bool
{
    for(int i=1;i<=m;i++)
    {
        if(dis[x][i] && !vis[i])
        {
            vis[i]=1;
            if(con[i]==0 || dfs(dfs,con[i]))
            {
                con[i]=x;
                return true;
            }
        }
    }
    return false;
};
int cnt=0;
for(int i=1;i<=n;i++)
{
    fill(vis.begin(),vis.end(),0);
    if(dfs(dfs,i)) cnt++;
}
cout<<cnt<<"\n";