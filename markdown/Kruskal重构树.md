# Kruskal重构树

```c++
DSU dsu(2*n);
for(auto &[u,v,w]: e) {
    int ls=dsu.find(u),rs=dsu.find(v);
    if(ls==rs) continue;
    ++tot;
    adj[tot].push_back(ls);
    adj[tot].push_back(rs);
    dsu.merge(tot,ls),dsu.merge(tot,rs);
    if(tot==2*n-1) break;
}
```

