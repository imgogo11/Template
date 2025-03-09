struct Point{int x,y;}a[N],tmp[N];
int n,b[N];
constexpr ll inf=5e18;
ll sqr(ll x){return x*x;}
ll dis(int l,int r){return sqr(a[l].x-a[r].x)+sqr(a[l].y-a[r].y);}
bool cmp(Point a,Point b){return a.x==b.x?a.y<b.y:a.x<b.x;}
void merge(int l,int r)
{
    int mid=(l+r)>>1,i=l,j=mid+1;//归并
    for(int k=l;k<=r;k++) {
        if(i<=mid && (j>r || a[i].y<a[j].y)) tmp[k]=a[i++];
        else tmp[k]=a[j++];
    }
    for(int i=l;i<=r;i++) a[i]=tmp[i];
}
ll mergeblock(int l,int r)
{
    if(l>=r) return inf;
    if(l+1==r) {
        if(a[l].y>a[r].y) swap(a[l],a[r]);
        return dis(l,r);
    }
    int mid=(l+r)>>1,t=a[mid].x,cnt=0;//重新排序后中位数就乱了，需要记下来
    ll d=min(mergeblock(l,mid),mergeblock(mid+1,r));
    merge(l,r);
    for(int i=l;i<=r;i++)
        if(sqr(a[i].x-t)<d)
            b[++cnt]=i;
    for(int i=1;i<=cnt;i++)
        for(int j=i+1;j<=cnt && sqr(a[b[j]].y-a[b[i]].y)<d;j++)
            d=min(d,dis(b[j],b[i]));
    return d;
}
void solve()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i].x>>a[i].y;
    sort(a+1,a+n+1,cmp);
    cout<<mergeblock(1,n)<<"\n";
}