# 自动取模类

```c++
template<class T>
constexpr T power(T a, ll b) {
    T res = 1;
    for (; b; b /= 2, a *= a)
        if (b % 2)
            res *= a;
    return res;
}
constexpr ll mul(ll a, ll b, ll p) {
    ll res = a * b - ll(1.L * a * b / p) * p;
    res %= p;
    if (res < 0) res += p;
    return res;
}
template<int P>
struct MInt {
    int x;
    constexpr MInt() : x{} {}
    constexpr MInt(ll x) : x{norm(x % getMod())} {}
    static int Mod;
    constexpr static int getMod() {
        return (P>0?P:Mod);
    }
    constexpr static void setMod(int Mod_) {Mod = Mod_;}
    constexpr int norm(int x) const {
        if (x < 0) x += getMod();
        if (x >= getMod()) x -= getMod();
        return x;
    }
    constexpr int val() const {return x;}
    explicit constexpr operator int() const {return x;}
    constexpr MInt operator-() const {
        MInt res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MInt inv() const {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }
    constexpr MInt &operator*=(MInt rhs) & {
        x = 1LL * x * rhs.x % getMod();
        return *this;
    }
    constexpr MInt &operator+=(MInt rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MInt &operator-=(MInt rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MInt &operator/=(MInt rhs) & {return *this *= rhs.inv();}
    friend constexpr MInt operator*(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MInt operator+(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MInt operator-(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MInt operator/(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr istream &operator>>(istream &is, MInt &a) {
        ll v;
        is >> v;
        a = MInt(v);
        return is;
    }
    friend constexpr ostream &operator<<(ostream &os, const MInt &a) {return os << a.val();}
    friend constexpr bool operator==(MInt lhs, MInt rhs) {return lhs.val() == rhs.val();}
    friend constexpr bool operator!=(MInt lhs, MInt rhs) {return lhs.val() != rhs.val();}
};
template<>
int MInt<0>::Mod = 998244353;
template<int V, int P>
constexpr MInt<P> CInv = MInt<P>(V).inv();
constexpr int P = 1000000007;
using Z = MInt<P>;
```

加减乘除+power+inv

```c++
ll mul(ll a,ll b) {return (__int128)a*b%Mod;}
void Mul(ll &a,ll b) {a*=b,a%=Mod;}
ll power(ll a,ll b) {
    ll res=1;
    while(b) {
        if(b&1) Mul(res,a);
        Mul(a,a);
        b>>=1;
    }
    return res;
}
ll inv(ll x) {return power(x,Mod-2);}
ll dim(ll a,ll b) {return (__int128)a*inv(b)%Mod;}
ll add(ll a,ll b) {return (a+b)%Mod;}
ll sub(ll a,ll b) {
    ll res=(a-b)%Mod;
    if(res<0) res+=Mod;
    return res;
}
void Div(ll &a,ll b) {a*=inv(b),a%=Mod;}
void Add(ll &a,ll b) {a+=b,a%=Mod;}
void Sub(ll &a,ll b) {
    a-=b,a%=Mod;
    if(a<0) a+=Mod;
}
```

