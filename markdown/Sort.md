### Mergesort

```c++
void mergesort(int l,int r) {
    if(l>=r) return;
    mergesort(l,(l+r)/2);
    mergesort((l+r)/2+1,r);
    int cnt=0,p1=l,p2=(l+r)/2+1;
    while(p1<=(l+r)/2 && p2<=r) {
        if(a[p1]>a[p2]) b[++cnt]=a[p2++];
        else b[++cnt]=a[p1++];
    }
    while(p1<=(l+r)/2) b[++cnt]=a[p1++];
    while(p2<=r) b[++cnt]=a[p2++];
    for(int i=1;i<=cnt;i++) a[l+i-1]=b[i];      
}
```

### Quicksort

```c++
void quick_sort(int l, int r) {
    if(l >= r) return;
    int i = l - 1, j = r + 1, x = a[range(l,r)];
    while(i < j) {
        do i++; while(a[i] < x);
        do j--; while(a[j] > x);
        if(i < j) swap(a[i], a[j]);
    }
    quick_sort(l, j), quick_sort(j + 1, r);
}
```
