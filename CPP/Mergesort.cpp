void mergesort(int l,int r) {
    if(l>=r)
        return;
    mergesort(l,(l+r)/2);
    mergesort((l+r)/2+1,r);
    int cnt=0,p1=l,p2=(l+r)/2+1;
    while(p1<=(l+r)/2 && p2<=r)
    {
        if(a[p1]>a[p2])
            b[++cnt]=a[p2++];
        else
            b[++cnt]=a[p1++];
    }
    while(p1<=(l+r)/2)
        b[++cnt]=a[p1++];
    while(p2<=r)
        b[++cnt]=a[p2++];
    for(int i=1;i<=cnt;i++)
        a[l+i-1]=b[i];      
}