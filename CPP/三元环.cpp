vector adj(n+1,vector<int>());
vector<int> dfn(n+1);
for(auto &[u,v]: edge) {
    if(d[u]>d[v] || (d[u]==d[v] && u>v)) swap(u,v);
    adj[u].push_back(v);
}
int ans=0;
for(auto &[u,v]: edge) {
    for(int to: adj[u])
        dfn[to]=u;
    for(int to: adj[v])
        if(dfn[to]==u)
            ans+=1;
}
cout<<ans<<"\n";



vector adj(n,bitset<N>());
for(int i=0;i<n;i++) {
    for(int j=0;j<n;j++) {
        char c;
        cin>>c;
        adj[i].set(j,c=='1');
    }
}
ll ans=0;
for(int i=0;i<n;i++)
    for(int j=i+1;j<n;j++)
        if(adj[i][j])
            ans+=(adj[i]&adj[j]).count();
cout<<ans/3<<"\n";