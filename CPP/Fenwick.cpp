struct Fenwick {
    vector<ll> Fbit;
    int n;
    Fenwick(){}
    Fenwick(int n) {init(n);}
    void init(int n) {
        Fbit.assign(n+5,0);
        this->n=n+1;
    }
    int lowbit(int x) {return x&(-x);}
    void add(int k1,ll k2) {
        for(int i=k1+1;i<=n;i+=lowbit(i))
            Fbit[i]+=k2;
    }
    ll presum(int z) {
        ll res=0;
        for(int i=z+1;i>=1;i-=lowbit(i))
            res+=Fbit[i];
        return res;    
    }
    ll sufsum(int z) {
        if(z>=n) return 0;
        return presum(n-1)-presum(z-1);    
    }
    ll rangesum(int l,int r) {
        if(l>r) return 0;
        return presum(r)-presum(l-1);
    }
    int select(const ll &k) {
        int x=0;
        ll cur=0;
        for (int i=(1<<__lg(n));i;i/=2) {
            if(x+i<=n && cur+Fbit[x+i]<k) {
                x+=i;
                cur=cur+Fbit[x];
            }
        }
        return x;
    }
};