### Segtree_dynamic

```c++
int tot,L,R;
struct segtree {
    struct Node {
        int l,r;
        ll sum,mx;
    };
    vector<Node> tr;
    segtree(){}
    segtree(int n) {init(n);}
    void init(int n) {
        tr.assign(2*n*__lg(R),{});//空间O(operations*logV)
    }
    void pushup(Node &u,Node &ls,Node &rs) {
        if(ls.mx>rs.mx) {
            u.mx=ls.mx;
            u.sum=ls.sum;
        }
        else if(ls.mx<rs.mx) {
            u.mx=rs.mx;
            u.sum=rs.sum;
        }
        else {
            u.mx=ls.mx;
            u.sum=ls.sum+rs.sum;
        }
    }
    void pushup(int p) {
        if(tr[p].l && tr[p].r)
            pushup(tr[p],tr[tr[p].l],tr[tr[p].r]);
        else {
            int ml=tr[p].l,mr=tr[p].r;
            if(!tr[p].r) tr[p]=tr[tr[p].l];
            else if(!tr[p].l) tr[p]=tr[tr[p].r];
            tr[p].l=ml,tr[p].r=mr;
        }
    }
    void upd(int p,int l,int r,int pos,int val) {
        if(l==r) {
            tr[p].mx+=val;
            tr[p].sum=l;
        }
        else {
            int mid=(l+r)>>1;
            if(pos<=mid) {
                if(!tr[p].l) tr[p].l=++tot;
                upd(tr[p].l,l,mid,pos,val);
            }
            else {
                if(!tr[p].r) tr[p].r=++tot;
                upd(tr[p].r,mid+1,r,pos,val);
            }
            pushup(p);
        }
    }
    void upd(int p,int pos,int val){
        upd(p,L,R,pos,val);
    }
    int merge(int x,int y,int l=L,int r=R) {
        if(!x || !y) return x+y;
        if(l==r) {
            tr[x].mx+=tr[y].mx;
            tr[x].sum=l;
            return x;
        }
        int mid=(l+r)>>1;
        tr[x].l=merge(tr[x].l,tr[y].l,l,mid);
        tr[x].r=merge(tr[x].r,tr[y].r,mid+1,r);
        pushup(x);
        return x;
    }
};
void solve()
{
    int n;
    cin>>n;
    tot=0,L=1,R=n;
    vector<int> a(n+1);
    segtree sg(n);
    vector adj(n+1,vector<int>());
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<n;i++) {
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> root(n+1);
    vector<ll> ans(n+1);
    auto dfs=[&](auto &&dfs,int u,int fa)->void {
        root[u]=++tot;
        for(int v: adj[u]) {
            if(v==fa) continue;
            dfs(dfs,v,u);
            sg.merge(root[u],root[v]);
        }
        sg.upd(root[u],a[u],1);
        ans[u]=sg.tr[root[u]].sum;
    };
    dfs(dfs,1,0);
    for(int i=1;i<=n;i++) cout<<ans[i]<<" \n"[i==n];
}
```

