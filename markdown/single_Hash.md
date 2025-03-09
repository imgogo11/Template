# 单哈希(由于int128,约普通双哈希6倍时长)

```c++
constexpr __int128 Mod=1000000000000000283LL;
constexpr __int128 Base=1000000033;
__int128 p[N];
void init()
{
    p[0]=1;
    for(int i=1;i<N;i++)
        p[i]=p[i-1]*Base%Mod;
}
struct Hash
{
    vector<__int128> h;
    Hash(){}
    Hash(const string &s){init(s);}
    void init(const string &s) {
        h.resize((int)s.size()+1);
        for(int i=1;i<=(int)s.size();i++) {
            h[i]=h[i-1]*Base%Mod+s[i-1];
            if(h[i]>=Mod) h[i]-=Mod;
        }
    }
    ll get(int l,int r) {
        if(l>r) return -1;
        __int128 ans=(h[r]-h[l-1]*p[r-l+1]%Mod)%Mod;
        if(ans<0) ans+=Mod;
        return ans;
    }
    ll get(const string &s) {
        __int128 ans=0;
        for(int i=1;i<=(int)s.size();i++) {
            ans=ans*Base%Mod+s[i-1];
            if(ans>=Mod) ans-=Mod;
        }
        return ans;
    }
};
```

