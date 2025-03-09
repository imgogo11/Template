### Pollard-Rho

时间复杂度$O(n^{\frac{1}{4}})$

```c++
mt19937_64 rng(time(0));
long double Inv;ll MOD;
void setmod(ll mod) {MOD=mod;Inv=(long double)1/MOD;}
ll mul(ll a,ll b)  {
    ll r=a*b-(ll)(a*Inv*b-0.5)*MOD; 
    return r<MOD?r:r-MOD;
}
ll add(ll a,ll b) {return a+=b,a>=MOD?a-MOD:a;}
ll power(ll a,ll b) {
    ll ans=1;
    while(b) {
        if(b&1) ans=mul(ans,a);
        a=mul(a,a);
        b>>=1;
    }
    return ans;
}
bool mr(ll n) {
    if(n<=2 || (!(n&1))) return n == 2;
    int t=__builtin_ctzll(n-1); 
    ll m=(n-1)>>t;setmod(n);
    for(int i=0;i<6;i++) {
        ll v=power(rng()%(n-2)+2,m);
        if(v==1) continue;
        for(int j=1;j<=t;j++) {
            if(v==n-1) break;
            if(j==t) return false;
            v=mul(v, v);
        }
    }
    return true;
}
ll rho(ll n) {
    if(!(n&1)) return 2;
    ll s=0,t=0,v=0,c=rng()%(n-1)+1;
    for(int i=1;;i<<=1) {
        v=1;s=t;
        for(int j=1;j<=i;j++) {
            t=add(mul(t,t),c);v=mul(v,abs(t-s));
            if(j==i || ((j&255) == 0)) {
                ll d=gcd(n,v);
                if(d>1) return d; 
            } 
        }
    }
    return 0;
}
vector<ll> prime_factor(ll n) 
{
    vector<ll> ans;
    auto D=[&](auto &&D,ll n)->void {
        if(n==1) return;
        if(mr(n)) return ans.push_back(n),void(); 
        ll m=rho(n);D(D,m);D(D,n/m);    
    };
    D(D,n);sort(begin(ans),end(ans));
    return ans;
}
vector<ll> factor(ll x) {
    auto div=prime_factor(x);
    vector<pair<ll,int>> p;
    ll lst=0;
    int cnt=0;
    for(auto v: div) {
        if(v==lst) cnt++;
        else if(lst==0) lst=v,cnt=1;
        else {
            p.emplace_back(lst,cnt);
            lst=v,cnt=1;
        }
    }
    p.emplace_back(lst,cnt);
    vector<ll> res;
    int lim=p.size();
    auto f=[&](auto &&f,ll now,int k)->void {
        if(k==lim) {
            res.emplace_back(now);
            return;
        }
        ll d=1;
        for(int i=0;i<=p[k].second;i++) {
            if(i>0) d*=p[k].first;
            f(f,d*now,k+1);
        }
    };
    f(f,1,0);
    return res;
}
```

