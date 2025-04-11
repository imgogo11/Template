struct Node {
    int l,r,val;
}tr[N<<5];//(更新前版本需update覆盖,不应手写modify更新,这样主席树数组也需要更大<<6)
int tot,root[N],b[N],a[N];
void build(int &k,int l,int r) {
    k=++tot;
    if(l==r)
        return;
    int mid=(l+r)>>1;
    build(tr[k].l,l,mid);
    build(tr[k].r,mid+1,r);
}//动态开点建树
void update(int &now,int pre,int l,int r,int kth,int val) {
    now=++tot; 
    tr[now]=tr[pre];
    tr[now].val+=val;
    if(l==r)
        return;
    int mid=(l+r)>>1;
    if(kth<=mid)
        update(tr[now].l,tr[pre].l,l,mid,kth,val);
    else
        update(tr[now].r,tr[pre].r,mid+1,r,kth,val);
}//求区间mex则需要再pushup数出现的位置
int query(int lp,int rp,int l,int r,int k) {//求区间第k大
    if(l==r)
        return b[l];
    int num=tr[tr[rp].l].val-tr[tr[lp].l].val;
    int mid=(l+r)>>1;
    if(k<=num)
        return query(tr[lp].l,tr[rp].l,l,mid,k);
    else
        return query(tr[lp].r,tr[rp].r,mid+1,r,k-num);
}
ll query(int lp,int rp,int l,int r,int x1,int x2) {//求区间[l,r]中x1<=X<=x2的数和
    if(x1<=l && r<=x2)
        return tr[rp].val-tr[lp].val;
    int mid=(l+r)>>1;
    ll ans=0;
    if(x1<=mid)
        ans+=query(tr[lp].l,tr[rp].l,l,mid,x1,x2);
    if(x2>mid)
        ans+=query(tr[lp].r,tr[rp].r,mid+1,r,x1,x2);
    return ans;
}
void solve() {
    int n,m,sum;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        cin>>a[i],b[i]=a[i];
    sort(b+1,b+n+1);
    sum=unique(b+1,b+n+1)-b-1;//离散化后的个数
    // build(root[0],1,sum);
    for(int i=1;i<=n;i++)
        update(root[i],root[i-1],1,sum,lower_bound(b+1,b+sum+1,a[i])-b,1);
    for(int i=1;i<=m;i++) {
        int l,r,k;
        cin>>l>>r>>k;
        cout<<query(root[l-1],root[r],1,sum,k)<<'\n';
    }
}