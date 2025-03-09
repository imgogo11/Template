### Dijkstra

不能求有负权图

![graph](D:\Template\graph.png)

理论结果:0 3 1 1      实际结果:0 3 1 2
复杂度$O(mlogm)$

```c++
vector<int> dis(n+1,inf),vis(n+1);
priority_queue<array<ll,2>,vector<array<ll,2>>,greater<>> pq;
auto dij=[&](int sp) {
    //fill(dis,dis+n+1,inf);fill(vis,vis+n+1,false);
    dis[sp]=0;
    pq.push({0,sp});
    while(!pq.empty()) {
        auto [d,u]=pq.top();
        pq.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(auto [v,w]: adj[u]) {
            if(dis[v]>d+w) {
                dis[v]=d+w;
                pq.push({dis[v],v});
            }
        }
    }
};
```

$n^2$暴力dijkstra
```c++
vector<int> dis(n+1,inf),vis(n+1);
auto dij=[&](int sp) {
    dis[sp]=0;
    for(int i=1;i<=n;i++) {
        int now=0;
        for(int j=1;j<=n;j++)
            if(!vis[j] && (!now || dis[j]<dis[now]))
                now=j;
        vis[now]=1;
        for(int j=1;j<=n;j++)
            dis[j]=min(dis[j],dis[now]+adj[now][j]);
    }
};
```

