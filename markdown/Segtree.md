### Segtree

```c++
ll a[N];
struct segtree
{
    struct Node {
        int l,r;
        ll ans,lz;
    };
    vector<Node> tr;
    segtree() {}
    segtree(int n) {init(n);}
    void init(int n) {tr.resize(4*n+10);}
    void pushup(Node &u,Node &ls,Node &rs) {
        u.ans=ls.ans+rs.ans;
    }
    void pushup(int p){pushup(tr[p],tr[p*2],tr[p*2+1]);}
    void pushdown(Node &u,ll x) {
        u.ans+=(u.r-u.l+1)*x;
        u.lz+=x;
    }
    void pushdown(Node &u,Node &ls,Node &rs)
    {if(u.lz) pushdown(ls,u.lz),pushdown(rs,u.lz),u.lz=0;}
    void pushdown(int p){pushdown(tr[p],tr[p*2],tr[p*2+1]);}
    void build(int p,int l,int r) {
        tr[p]={l,r,0,0};
        if(l==r) {
            tr[p]={l,r,a[l],0};
            return;
        }
        int mid=(l+r)>>1;
        build(p*2,l,mid);
        build(p*2+1,mid+1,r);
        pushup(p);
    }
    void update(int p,int x,int y,ll z) {
        if(x<=tr[p].l && tr[p].r<=y) {
            pushdown(tr[p],z);
            return;
        }
        pushdown(p);
        int mid=(tr[p].l+tr[p].r)>>1;
        if(x<=mid) update(p*2,x,y,z);
        if(y>mid) update(p*2+1,x,y,z);
        pushup(p);
    }
    Node query(int p,int x,int y) {
        if(x<=tr[p].l && y>=tr[p].r)
            return tr[p];
        pushdown(p);
        int mid=(tr[p].l+tr[p].r)>>1;
        Node r1,r2,r3;
        if(y<=mid) return query(p*2,x,y);
        if(x>mid) return query(p*2+1,x,y);
        r1=query(p*2,x,y),r2=query(p*2+1,x,y);
        r3.l=r1.l,r3.r=r2.r;
        pushup(r3,r1,r2);
        return r3;
    }
};
```

