bool flag;
vector<ll> B;
void insert(ll x) {
    for(auto b : B) x=min(x,b^x);
    for(auto &b : B) b=min(b,b^x);
    if(x) B.push_back(x);
    else flag=true;
}
ll kth(ll k) {
    k-=flag;
    if(!k) return 0;
    if(k>=(1LL<<B.size())) return -1;
    ll ans=0;
    for(int i=0;i<B.size();i++)
        if((k>>i)&1)
            ans^=B[i];
    return ans;
}
ll qmax() {
    ll ans=0;
    for(const auto &b: B)
        ans^=b;
    return ans;
}
ll qmin() {
    if(flag) return 0;
    return B.front();
}
bool check(ll x) {
    if(flag && !x) return true;
    else if(!x) return false;
    for(auto b : B) x=min(x,b^x);
    if(x) return false;
    return true;
}
sort(B.begin(),B.end());//对线性基排序



constexpr int MAXBIT = 50;//(Gauss)
ll a[MAXBIT+1],tmp[MAXBIT+1],cnt;
bool flag;
void insert(ll x)
{
    for(int i=MAXBIT;i>=0;i--) {
        if((x>>i)&1) {
            if(!a[i]) {
                a[i]=x;
                return;
            }
            else x^=a[i];
        }
    }
    flag=true;
}
bool check(ll x)
{
    if(flag && !x) return true;
    else if(!x) return false;
    for(int i=MAXBIT;i>=0;i--)
    {
        if((x>>i)&1)
        {
            if(!a[i]) return false;
            else x^=a[i];
        }
    }
    return true;
}
ll qmax(ll res=0)
{
    for(int i=MAXBIT;i>=0;i--)
        res=max(res,res^a[i]);
    return res;
}
ll qmin()
{
    if(flag) return 0;
    for(int i=0;i<=MAXBIT;i++)
        if(a[i])
            return a[i];
}
ll query(ll k)
{
    k-=flag;
    if(!k) return 0;
    if(k>=(1LL<<cnt)) return -1;
    ll res=0;
    for( int i=0;i<cnt;i++)
        if((k>>i)&1)
            res^=tmp[i];
    return res;
}
for(int i=0;i<=MAXBIT;i++)//求最终的线性基
{
    if(a[i]==0) continue;
    for(int j=i-1;j>=0;j--)
    {
        if((a[i]>>i)&1)
            a[i]^=a[j];
    }
    if(a[i]) tmp[cnt++]=a[i];
}