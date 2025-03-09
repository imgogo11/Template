### Kruskal

```c++
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
struct E {
    ll u,v,w;
    bool operator < (const E &ano)const {
        if(w!=ano.w) return w<ano.w;
        if(u!=ano.u) return u<ano.u;
        return v<ano.v;
    }
};
void solve() {
    auto kruskal=[&]()->ll {
        sort(edge.begin(),edge.end());
        DSU dsu(n);
        ll cnt=0,sum=0;
        for(auto &[u,v,w]: edge) {
            if(dsu.same(u,v)) continue;
            dsu.merge(u,v);
            cnt+=1;
            sum+=w;
        }
        if(cnt!=n-1) return LNF;
        return sum;
    };
}
```

