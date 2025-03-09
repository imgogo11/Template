ll mul(ll a,ll b,ll mod) {return (__int128_t)a*b%mod;}
ll power(ll a,ll b,ll mod) {
    ll res=1%mod;
    while(b) {
        if(b&1) res=mul(res,a,mod);
        a=mul(a,a,mod);
        b>>=1;
    }
    return res;
}
bool isprime(ll n) {
    if(n==2) return true;
    if(n<=1 || n%2==0) return false;
    ll base[7]={2,325,9375,28178,450775,9780504,1795265022};
    ll u=n-1,k=0;
    while(u%2==0) u/=2,k++;
    for(ll x : base) {
        if(x%n==0) continue;
        ll v=power(x,u,n);
        if(v==1 || v==n-1) continue;
        for(int j=1;j<=k;j++) {
            ll last=v;
            v=mul(v,v,n);
            if(v==1) {
                if(last!=n-1) return false;
                break;
            }
        }
        if(v!=1) return false;
    }
    return true;
}