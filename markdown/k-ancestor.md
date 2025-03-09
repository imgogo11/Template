### k-ancestor

$O(nlogn)$预处理—$O(1)$查询

```c++
vector<int> vt[N],anc[N],des[N];
int dep[N],fa[20][N],son[N],top[N],len[N],dfn[N],mdfn[N],id[N],cnt,root;
void dfs1(int u)
{
    len[u]=1;
    dep[u]=dep[fa[0][u]]+1;
    for (int v : vt[u])
    {
        if(v==fa[0][u])
            continue;
        fa[0][v]=u;
        dfs1(v);
        if(len[v]+1>len[u])
            son[u]=v,len[u]=len[v]+1;
    }
}
void dfs2(int u,int topfa)
{
    dfn[u]=++cnt,top[u]=topfa,id[cnt]=u;
    if(son[u])
        dfs2(son[u],topfa);
    for (int v : vt[u])
    {
        if(v==fa[0][u] || v==son[u])
            continue;
        dfs2(v,v);
    }
    mdfn[u]=cnt;
}
void cut(int r=1)
{
    dfs1(r);
    dfs2(r,r);
}
int find(int u,int k)//查询u的k级祖先
{
    if(k==0)
        return u;
    int step=__lg(k),now=fa[step][u];
    int d=k-(1<<step)+dep[top[now]]-dep[now];
    if(d>0)
        return anc[top[now]][d];
    else
        return des[top[now]][-d];
}
void solve()
{   
    for(int i=1;i<=n;i++)
    {
        cin>>fa[0][i];
        vt[fa[0][i]].push_back(i);
        if(!fa[0][i]) root=i;
    }
    cut(root);
    for(int i=1;i<=__lg(n);i++)
        for(int j=1;j<=n;j++)
            fa[i][j]=fa[i-1][fa[i-1][j]];
    for(int i=1;i<=n;i++)
    {
        if(top[i]==i)
        {
            for(int j=0;j<len[i];j++)
                des[i].push_back(id[dfn[i]+j]);
            int now=i;
            for(int j=0;j<len[i];j++)
            {
                anc[i].push_back(now);
                now=fa[0][now];
            }
        }
    }
}
```

