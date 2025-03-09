### NTT(多项式乘法)

更换Mod时同时需要修改原根e
$998244353-->3(原根)--->31、89$ 
$1004535809-->3(原根)--->4172$ 
以下和会爆int，同时有的还需要__int128来乘法取模
$2013265921--->137$ 
$4179340454199820289LL--->5198941775LL$      由于i128乘法以及取模，跑不动$10^6$数据范围

```c++
constexpr int Mod=998244353;
int power(ll a,ll b) {
    ll res=1;
    while(b) {
        if(b&1) res=res*a%Mod;
        a=a*a%Mod;
        b>>=1;
    }
    return res;
}
vector<int> rev, roots {0,1};
void dft(vector<int> &a) {
    int n=a.size();
    if(int(rev.size())!=n) {
        int k=__builtin_ctz(n)-1;
        rev.resize(n);
        for(int i=0;i<n;i++)
            rev[i]=rev[i>>1]>>1 | (i&1)<<k;
    }
    for(int i=0;i<n;i++)
        if(rev[i]<i)
            swap(a[i],a[rev[i]]);
    if(roots.size()<n) {
        int k=__builtin_ctz(roots.size());
        roots.resize(n);
        while((1<<k)<n) {
            int e=power(31,1<<(__builtin_ctz(Mod-1)-k-1));//Mod变后此处底数也需要修改
            //此处power底数并非为原根，是findPrimitiveRoot()函数的值
            for(int i=1<<(k-1);i<(1<<k);i++) {
                roots[2*i]=roots[i];
                roots[2*i+1]=1LL*roots[i]*e%Mod;
            }
            k++;
        }
    }
    for(int k=1;k<n;k*=2) {
        for(int i=0;i<n;i+=2*k) {
            for(int j=0;j<k;j++) {
                int u=a[i+j];
                int v=1LL*a[i+j+k]*roots[k+j]%Mod;
                a[i+j]=(u+v)%Mod;
                a[i+j+k]=(u-v+Mod)%Mod;//
            }
        }
    }
}
void idft(vector<int> &a) {
    int n=a.size();
    reverse(a.begin() + 1, a.end());
    dft(a);
    int inv=(1-Mod)/n+Mod;//
    for(int i=0;i<n;i++)
        a[i]=1LL*a[i]*inv%Mod;
}
vector<int> mul(vector<int> a,vector<int> b) {
    int n=1,tot=a.size()+b.size()-1;
    while(n<tot) n*=2;
//    if(tot<128) {//测试时将暴力特判情况注释
//        vector<int> c(a.size() + b.size() - 1);
//        for(int i=0;i<a.size();i++)
//            for(int j=0;j<b.size();j++)
//                c[i+j]=(c[i+j]+1LL*a[i]*b[j])%Mod;
//        return c;
//    }
    a.resize(n);b.resize(n);
    dft(a);dft(b);
    for(int i=0;i<n;i++)
        a[i]=1LL*a[i]*b[i]%Mod;
    idft(a);
    a.resize(tot);
    return a;
}
```

找原根（返回值不是原根，对应的i值可能是）

```c++
constexpr ll findPrimitiveRoot() {
    ll i=2;
    int k=__builtin_ctz(P-1);
    while(1) {
        if(power(i, (P - 1) / 2) != 1) break;
        i+=1;
    }
    return power(i,(P-1)>>k);
}
```

