auto cdq=[&](auto &&cdq,int l,int r)->void {
    if(l>=r) return;
    int mid=(l+r)>>1;
    cdq(cdq,l,mid);
    cdq(cdq,mid+1,r);
    // sort(a.begin()+l,a.begin()+mid+1,[&](array<int,5> x,array<int,5> y) {
    //     if(x[1]!=y[1]) return x[1]<y[1];
    //     return false;
    // });
    // sort(a.begin()+mid+1,a.begin()+r+1,[&](array<int,5> x,array<int,5> y) {
    //     if(x[1]!=y[1]) return x[1]<y[1];
    //     return false;
    // });
    int p1=l,p2=mid+1,cnt=l;
    while(p1<=mid || p2<=r) {
        if(p2>r || (p1<=mid && a[p1][1]<=a[p2][1])) {
            b[cnt++]=a[p1];
            tree.add(a[p1][2],a[p1][3]);
            p1++;
        }
        else {
            a[p2][4]+=tree.presum(a[p2][2]);
            b[cnt++]=a[p2];
            p2++;
        }
    }
    for(int i=l;i<=mid;i++) {
        tree.add(a[i][2],-a[i][3]);
    }
    for(int i=l;i<=r;i++)
        a[i]=b[i];
};
