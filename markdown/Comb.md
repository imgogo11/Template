### Comb

A为排列数,C为组合数,Fac为阶乘,Invfac为阶乘的逆
模数必须为质数

```c++
struct Comb
{
    int n;
    vector<ll> fac,invfac,inv;
    Comb() : fac{1}, invfac{1}, inv{0} {}
    Comb(int n) : Comb() {init(n);}
    void init(int n) {
        this->n=n;
        fac.resize(n+1),invfac.resize(n+1),inv.resize(n+1);
        for(int i=1;i<=n;i++) 
            fac[i]=fac[i-1]*i%Mod;
        invfac[n]=power(fac[n],Mod-2);
        for(int i=n;i>=1;i--) {
            invfac[i-1]=invfac[i]*i%Mod;
            inv[i]=invfac[i]*fac[i-1]%Mod;
        }
    }
    ll A(int n,int m) {
        if(n<m || m<0) return 0;
        return fac[n]*invfac[n-m]%Mod;
    }
    ll C(int n,int m) {
        if(n<m || m<0) return 0;
        return fac[n]*invfac[m]%Mod*invfac[n-m]%Mod;
    }
    ll Fac(int m) {return fac[m];}
    ll Invfac(int m) {return invfac[m];}
    ll Inv(int m) {return inv[m];}
}comb(N);
ll inv(ll x) {return power(x,Mod-2);}
```

---

模数不为质数时暴力预处理

$C^{n}_{m}=C^{n-1}_{m-1}+C^{n}_{m-1}$

```c++
vector C(n+1,vector<int>(n+1,0));
for(int i=0;i<=n;i++) {
    C[i][0]=1;
    for(int j=1;j<=i;j++)
        C[i][j]=(C[i-1][j-1]+C[i-1][j])%Mod;
}
```

