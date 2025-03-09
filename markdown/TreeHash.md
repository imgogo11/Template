### TreeHash


TreeHash通常用来比较两棵树是否同构
无根树通常通过找重心,然后进行hash判断同构

```c++
mt19937_64 rng{chrono::steady_clock::now().time_since_epoch().count()};
const ull base = rng();
ull shift(ull x) {
    x^=(x<<14)^(x>>7)^(x<<21);
    x^=(x<<9)^(x>>17)^(x<<10);
    x^=(x<<3)^(x>>20)^(x<<19);
    return x;
}
ull h[N];
int sz[N],mxsz[N],n;
vector<int> adj[N];
void dfs1(int u,int p) {
    sz[u]=1,mxsz[u]=0;
    for(int v: adj[u]) {
        if(v==p) continue;
        dfs1(v,u);
        sz[u]+=sz[v];
        mxsz[u]=max(mxsz[u],sz[v]);
    }
    mxsz[u]=max(mxsz[u],n-sz[u]);
    if(mxsz[u]<=n/2) {
        //center
    }
}
void dfs2(int u,int p) {
    h[u]=base;
    for(int v: adj[u]) {
        if(v==p) continue;
        dfs2(v,u);
        h[u]+=h[v];
    }
    h[u]=shift(h[u]);
}

```

