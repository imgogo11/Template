auto prim=[&]()->ll {
    vector<ll> dis(n+1,LNF); vector<int> vis(n+1,0);
    ll sum=0;
    for(int i=1;i<=n;i++) {
        int x=0;
        for(int j=1;j<=n;j++)
            if(!vis[j] && (!x || dis[j]<dis[x]))
                x=j;
        vis[x]=1;
        if(i>1 && dis[x]==LNF) return LNF;
        if(i>1) sum+=dis[x];
        for(int i=1;i<=n;i++) dis[i]=min(dis[i],adj[x][i]);
    } return sum;
};



struct To {
    ll v,w;
    bool operator < (const To &ano) const {
        if(w!=ano.w) return w>ano.w;
        return 0;
    }
};
auto prim=[&]()->ll {
    priority_queue<To> q;
    vector<ll> dis(n+1,LNF); vector<int> vis(n+1,0);
    ll sum=0,cnt=0; q.push({1,0});
    while(!q.empty()) {
        auto [u,d]=q.top();
        q.pop();
        if(vis[u]) continue;
        vis[u]=1,sum+=d,cnt++;
        for(auto &[v,w]: adj[u]) {
            if(dis[v]>w) {
                dis[v]=w;
                q.push({v,w});
            }
        }
    }
    if(cnt<n) return LNF;
    return sum;
};