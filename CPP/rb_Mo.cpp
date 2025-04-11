int L[N],R[N],col[N],cnt[N],a[N],x[N],n,m,q,sz,tot;
void build() {
    sz=sqrt(n);
    tot=n/sz;
    for(int i=1;i<=tot;i++) {
        L[i]=(i-1)*sz+1,R[i]=i*sz;
        for(int j=L[i];j<=R[i];j++) col[j]=i;
    }
    if(R[tot]<n) {
        tot++;
        L[tot]=R[tot-1]+1,R[tot]=n;
        for(int j=L[tot];j<=R[tot];j++) col[j]=tot;
    }
}
struct Query {
    int l,r,id;
    bool operator < (const Query &A) const{
        if(col[l]!=col[A.l]) return col[l]<col[A.l];
        return r<A.r;
    }
};
void add(int val,ll &ans) {
    cnt[val]++;
    ans=max(ans,1LL*cnt[val]*x[val]);
}
void del(int val) {cnt[val]--;}
void solve() {
    cin>>n>>q;
    build();
    for(int i=1;i<=n;i++) {
        cin>>a[i];
        x[i]=a[i];
    }
    sort(x+1,x+n+1);
    m=unique(x+1,x+n+1)-x-1;
    for(int i=1;i<=n;i++)  a[i]=lower_bound(x+1,x+m+1,a[i])-x;
    vector<Query> Q(q+1);
    for(int i=1;i<=q;i++) {
        cin>>Q[i].l>>Q[i].r;
        Q[i].id=i;
    }
    sort(Q.begin()+1,Q.end());
    int l=1,r=0,lst_bk=0;
    ll Ans=0;
    vector<int> bf(n+1);
    vector<ll> ans(q+1);
    for(int i=1;i<=q;i++) {
        if(col[Q[i].l]==col[Q[i].r]) {//同一块则暴力扫
            for(int j=Q[i].l;j<=Q[i].r;j++) {
                bf[a[j]]++;
                ans[Q[i].id]=max(ans[Q[i].id],1LL*bf[a[j]]*x[a[j]]);
            }
            for(int j=Q[i].l;j<=Q[i].r;j++) bf[a[j]]--;
            continue;
        }
        if(col[Q[i].l]!=lst_bk) {//访问到新左端点块，重新初始化莫队
            while(r>R[col[Q[i].l]]) del(a[r]),r--;
            while(l<=R[col[Q[i].l]]) del(a[l]),l++;
            Ans=0;
            lst_bk=col[Q[i].l];
        }
        while(r<Q[i].r) ++r,add(a[r],Ans);//扩展右端点
        ll tmp_l=l,tmp=Ans;
        while(tmp_l>Q[i].l) --tmp_l,add(a[tmp_l],tmp);//扩展左端点
        ans[Q[i].id]=tmp;
        while(tmp_l<l) del(a[tmp_l]),++tmp_l;//回滚
    }
    for(int i=1;i<=q;i++) cout<<ans[i]<<"\n";
}