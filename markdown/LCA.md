### LCA

$O(n)$预处理—$O(logn)$查询

```c++
vector<int> adj[N];
int fa[N],dep[N],top[N],sz[N],son[N];
void dfs1(int u) {
    sz[u]=1;
    dep[u]=dep[fa[u]]+1;
    for(auto v : adj[u]) {
        if(v==fa[u])
            continue;
        fa[v]=u;
        dfs1(v);
        sz[u]+=sz[v];
        if(sz[v]>sz[son[u]])
            son[u]=v;
    }
}
void dfs2(int u,int topfa) {
    top[u]=topfa;
    if(son[u])
        dfs2(son[u],topfa);
    for(auto v : adj[u]) {
        if(v==fa[u] || v==son[u])
            continue;
        dfs2(v,v);
    }
}
void cut(int r=1) {
    dfs1(r);
    dfs2(r,r);
}
int lca(int x,int y) {
    while(top[x]!=top[y]) {
        if(dep[top[x]]>dep[top[y]]) x=fa[top[x]];
        else y=fa[top[y]];
    }
    return (dep[x]<dep[y]?x:y);
}
```

---

$O(nlogn)$预处理—$O(logn)$查询
注意多组的**预处理数组清空**!!!
注意会不会访问到>dep的祖先(即实际上不存在的点),可能导致错误的倍增上跳(用未更新过的数组值倍增向上跳了)
一般来说,固定倍增数组大小为常数D,固定更新和查询循环也为D就不会出现这种问题

```c++
int f[N][21],d[N],n,m,s;
vector<int> vt[N];
void dfs(int u,int fa)
{
    d[u]=d[fa]+1;
    f[u][0]=fa;
    for(int i=1;i<=__lg(d[u]);i++)
        f[u][i]=f[f[u][i-1]][i-1];
    for(int v : vt[u])
        if(v!=fa)
            dfs(v,u);
}
int lca(int a,int b)
{
    if(d[a]<d[b])
        swap(a,b);
    int deplimit=__lg(d[a]);
    for(int i=deplimit;i>=0;i--) {
        if(i>deplimit) continue;
        if(d[a]-(1<<i)>=d[b])
            a=f[a][i],deplimit=__lg(d[a]);
    }
    if(a==b) return a;
    for(int i=deplimit;i>=0;i--) {
        if(i>deplimit) continue;
        if(f[a][i]!=f[b][i])
            a=f[a][i],b=f[b][i],deplimit=__lg(d[a]);
    }
    return f[a][0];
}
void solve()
{
    memset(f,0,sizeof(int)*(n+5)*21);//!!!!
}
```

