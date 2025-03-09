constexpr int inf=2e9;
int sign(ll x) {return (x>0)-(x<0);}// 符号
struct Fraction {// 注意分数比较爆long long
    ll a,b;
    Fraction(ll a,ll b) : a(sign(a^b)*abs(a)/gcd(a,b)),b(abs(b)/gcd(a,b)) {}
    bool operator<=(const Fraction &o) const {return a*o.b<=b*o.a;}
};
struct Convex_opt {
    struct Line {
        ll k,b;
        Fraction x={-inf,1};
        ll operator[](ll x) const{return k*x+b;}
        Fraction operator&(const Line &l) const {return {l.b-b,k-l.k};} // 交点横坐标
    };
    deque<Line> q;
    void update(const Line &l) {
        auto x={-inf,1};
        while(!q.empty() && (x=(l&q.back()))<=q.back().x) 
            q.pop_back();
        q.push_back({l.k,l.b,x});
    }
    ll query(ll x) {
        Fraction fx={x,1};
        while(q.size()>1 && q[1].x<=fx)
            q.pop_front();
        q.front().x={-inf,1};
        return q.front()[x];
    }
};
//solve()
auto K=[&](int x) {return -2LL*h[x];};
auto X=[&](int x) {return 1LL*h[x];};
auto A=[&](int x) {return 1LL*h[x]*h[x]+c;};
auto B=[&](int x) {return dp[x]+1LL*h[x]*h[x];};

Convex_opt cvx;
for(int i=1;i<=n;i++) {
    if(i>1) dp[i]=cvx.query(X(i))+A(i);
    cvx.update({K(i),B(i)});
}