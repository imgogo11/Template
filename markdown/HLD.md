### HLD

维护边权则将边权放到儿子上进行维护,询问操作时注意最后两点关系
最后判断,若$x=y$则无需再询问,否则询问$query(1,dfn[y]+1,dfn[x]);~~~~~~~~$修改和查询同理

```c++
int w[N],wt[N],dfn[N],cnt;int sz[N],fa[N],dep[N],son[N],top[N];
vector<int> adj[N];
struct segtree {tr[p]={l,r,wt[l],0};}sg;
void dfs1(int u) {
    sz[u]=1,dep[u]=dep[fa[u]]+1;
    for(int v : adj[u]) {
        if (v!=fa[u]) {
            fa[v]=u;
            dfs1(v);
            sz[u]+=sz[v];
            if(sz[v]>sz[son[u]]) son[u]=v;
        }
    }
}
void dfs2(int u,int topfa) {
    dfn[u]=++cnt,wt[cnt]=w[u],top[u]=topfa;
    if(son[u]) dfs2(son[u],topfa);
    for(int v : adj[u]) {
        if (v==fa[u] || v==son[u]) continue;
        dfs2(v,v);
    }
}
void cut(int r=1) {dfs1(r);dfs2(r,r);}
void update_path(int x, int y, int z) {
    while(top[x]!=top[y]) {
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        sg.update(1,dfn[top[x]],dfn[x],z);
        x=fa[top[x]];
    }
    if(dep[x]<dep[y]) swap(x,y);
    sg.update(1,dfn[y],dfn[x],z);
}
ll query_path(int x,int y) {
    ll res=0;
    while (top[x]!=top[y]) {
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        res+=sg.query(1,dfn[top[x]],dfn[x]).ans;
        x=fa[top[x]];
    }
    if(dep[x]<dep[y]) swap(x,y);
    res+=sg.query(1,dfn[y],dfn[x]).ans;
    return res;
}
void update_tree(int x,int z){sg.update(1,dfn[x],dfn[x]+sz[x]-1,z);}
ll query_tree(int x){return sg.query(1,dfn[x],dfn[x]+sz[x]-1).ans;}
```

