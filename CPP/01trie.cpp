constexpr int N = 1e5 + 10;
constexpr int MAXBIT = 32;
ll t[N<<5][2],ans[N<<5],idx;
int newnode() {
    memset(t[idx],0,sizeof t[idx]);
    ans[idx]=0;
    return idx++;
}
void init() {
    memset(t[0],0,sizeof t[0]);
    ans[0]=0;
    idx=1;
}
void insert(ll x) {
    int p=0,c;
    for(ll i=MAXBIT;i>=0;i--) {
        c=(x>>i)&1;
        if(!t[p][c])
            t[p][c]=newnode();
        p=t[p][c];
    }
    ans[p]=x;
}
ll find(ll x) {
    int p=0,c;
    for(ll i=MAXBIT;i>=0;i--) {
        c=(x>>i)&1;
        if(t[p][c^1])
            p=t[p][c^1];
        else
            p=t[p][c];
    }
    return ans[p];
}