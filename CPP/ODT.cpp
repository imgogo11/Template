int a[N],n,m;
struct node {
    int l, r;
    mutable int v;
    node(ll l, ll r, ll v) : l(l), r(r), v(v) {}
    bool operator < (const node &a) const {
        return l < a.l;
    }
};
set<node> s;
auto split(int x) {
    if (x > n) return s.end();
    auto it = --s.upper_bound({x, 0, 0});
    if (it -> l == x) return it;
    int l = it -> l, r = it -> r, v = it -> v;
    s.erase(it);
    s.insert({l, x - 1, v});
    return s.insert({x, r, v}).first; 
}
void add(int l, int r, int x) {
    auto itr = split(r + 1), itl = split(l);
    for (auto it = itl; it != itr; it++) {
        it -> v += x;
    }
}
void assign(int l, int r, int x) {
    auto itr = split(r + 1), itl = split(l);
    s.erase(itl, itr);
    s.insert({l, r, x});
}
void solve()
{
    while(cin>>n>>m)
    {
        int init=1,l,r,v;
        s.clear();
        for(int i=1;i<=n;i++)
        {
            cin>>a[i];
            if(a[i]==a[init])
                continue;
            s.insert(node(init,i-1,a[init]));
            init=i;
        }
        s.insert(node(init,n,a[n]));
        for(int i=1;i<=m;i++)
        {
            cin>>l>>r>>v;
            auto it1=s.lower_bound(node(l,0,0));
            ll res=0,cnt=0;
            if(it1==s.end() || (it1->l)>l)
                it1--;
            while(it1!=s.end())
            {
                res+=(ll)(min(r,it1->r)-max(l,it1->l)+1)*(it1->v);
                if((it1->v)==v)
                    cnt+=(min(r,it1->r)-max(l,it1->l)+1);
                if(r<=it1->r)
                    break;
                it1++;
            }
            cout<<cnt<<' '<<res<<'\n';
            assign(l,r,v);
        }
    }
}