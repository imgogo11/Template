constexpr ll MOD1=1000000123,MOD2=1000001011;
constexpr ll BASE1=157,BASE2=211;
ll p1[N],p2[N];
void init() {
    p1[0]=p2[0]=1;
    for(int i=1;i<N;i++) {
        p1[i]=p1[i-1]*BASE1%MOD1;
        p2[i]=p2[i-1]*BASE2%MOD2;
    }
}
struct Hash {
    vector<ll> h1,h2;
    Hash() {}
    Hash(const string &s) {init(s);}
    void init(const string &s) {
        h1.resize((int)s.size()+1);
        h2.resize((int)s.size()+1);
        for(int i=1;i<=(int)s.size();i++) {
            h1[i]=h1[i-1]*BASE1%MOD1+s[i-1];
            if(h1[i]>=MOD1) h1[i]-=MOD1;
            h2[i]=h2[i-1]*BASE2%MOD2+s[i-1];
            if(h2[i]>=MOD2) h2[i]-=MOD2;
        }
    }
    pair<ll,ll> get(int l,int r) {
        if(l>r) return {-1,-1};
        ll part1=(h1[r]-h1[l-1]*p1[r-l+1]%MOD1)%MOD1;
        if(part1<0) part1+=MOD1;
        ll part2=(h2[r]-h2[l-1]*p2[r-l+1]%MOD2)%MOD2;
        if(part2<0) part2+=MOD2;
        return {part1,part2};
    }
    pair<ll,ll> get(const string &s) {
        ll part1=0,part2=0;
        for(int i=1;i<=(int)s.size();i++) {
            part1=part1*BASE1%MOD1+s[i-1];
            if(part1>=MOD1) part1-=MOD1;
            part2=part2*BASE2%MOD2+s[i-1];
            if(part2>=MOD2) part2-=MOD2;
        }
        return {part1,part2};
    }
};