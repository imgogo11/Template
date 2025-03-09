int Cantor(vector<int> &a)
{
    int n=a.size()-1;
    Fenwick fw(n);
    vector<ll> fac(n+1);
    fac[0]=1;
    for(int i=1;i<=n;i++) {
        fac[i]=fac[i-1]*i%Mod;
        fw.add(i,1);
    }
    ll rank=0;
    for(int i=1;i<=n;i++) {
        fw.add(a[i],-1);
        rank+=fw.presum(a[i])*fac[n-i]%Mod;
        rank%=Mod;
    }
    return (rank+1)%Mod;
}
vector<int> invCantor(int n,ll k)
{
    vector<int> a;
    Fenwick fw(n);
    vector<ll> fac(n+1);
    fac[0]=1;
    for(int i=1;i<=n;i++) {
        fac[i]=fac[i-1]*i%Mod;
        fw.add(i,1);
    }
    for(int i=1;i<=n;i++) {
        int now=k/fac[n-i];
        int val=fw.select(now+1);
        a.push_back(val);
        fw.add(val,-1);
        k=k%fac[n-i];
    }
    return a;
}