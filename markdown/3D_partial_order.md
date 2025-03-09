# CDQ

首先按第一维排序，然后对第二维归并排第二维，在排序第二维过程中，计算左半区间对右半区间的贡献(此时能保证，第一维、第二维都满足偏序关系，左半数增加贡献，右半数计算满足第三维关系的数量即可)
当偏序三维都有等于号时，即$a1\le a2~~b1\le b2~~c1\le c2$时，将原数组先去重方便统计

##### 归并版本     $O(nlog^2n)$ 

```c++
vector<array<int,5>> a(n+1),b(n+1);//0 1 2维度为属性，3为重复个数，4为当前a,b,c答案
int cnt=0;
for(int i=1,j=0;i<=n;i++) {
    j++;
    if(i==n || b[i]!=b[i+1]) {
        a[++cnt]=b[i];
        a[cnt][3]=j;
        j=0;
    }
}
auto cdq=[&](auto &&cdq,int l,int r)->void {
    if(l>=r) return;
    int mid=(l+r)>>1;
    cdq(cdq,l,mid);
    cdq(cdq,mid+1,r);
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
cdq(cdq,1,cnt);
vector<int> c(n+1);
for(int i=1;i<=cnt;i++) {
    c[a[i][4]+a[i][3]-1]+=a[i][3];
}
for(int i=0;i<n;i++) {
    cout<<c[i]<<"\n";
}
```

##### 非归并版本(直接按第二维sort即可,这种情况树状数组带log,不归并时间复杂度变化不大)    $O(nlog^2n)$ 

```c++
auto cdq=[&](auto &&cdq,int l,int r)->void {
    if(l>=r) return;
    int mid=(l+r)>>1;
    cdq(cdq,l,mid);
    cdq(cdq,mid+1,r);
    sort(a.begin()+l,a.begin()+mid+1,[&](array<int,5> x,array<int,5> y) {
        if(x[1]!=y[1]) return x[1]<y[1];
        return false;
    });
    sort(a.begin()+mid+1,a.begin()+r+1,[&](array<int,5> x,array<int,5> y) {
        if(x[1]!=y[1]) return x[1]<y[1];
        return false;
    });
    int p1=l,p2=mid+1,cnt=l;
    while(p1<=mid || p2<=r) {
        if(p2>r || (p1<=mid && a[p1][1]<=a[p2][1])) {
            tree.add(a[p1][2],a[p1][3]);
            p1++;
        }
        else {
            a[p2][4]+=tree.presum(a[p2][2]);
            p2++;
        }
    }
    for(int i=l;i<=mid;i++) {
        tree.add(a[i][2],-a[i][3]);
    }
};
```

