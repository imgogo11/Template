# 斜率/凸壳优化DP

对比下列两个$dp$转移式子:
$$
dp[j]=max_{i\in[l,r]}(dp[i]+(h[j]-h[i])+C) \\
dp[j]=max_{i\in[l,r]}(dp[i]+(h[j]-h[i])^2+C) \\
$$
对于第一个式子可转化成:$dp[j]-h[j]=max_{i\in[l,r]}(dp[i]-h[i])+C$,维护$dp[k]-h[k]$,区间查询最大值即可
对于第二个式子转化后为:$dp[j]=-2h_ih_j+(dp[i]+h_i^2)+(h_j^2+C)$,只有$h_i$有单调性,我们维护不了某个值
但是第二个式子转换后为形如:$Y(j)=K(i)X(j)+B(i)+A(j)$这样的形式
该形式即为典型的凸壳/斜率优化$DP$ 

### 凸壳优化DP

![slope](D:\Template\slope.png)

下式$Y(j)=K(i)X(j)+B(i)+A(j)$当,$K(i)$存在单调性即可通过凸壳优化。
若**$K$单调递增**，我们可以尾部通过单调队列思想，计算当前直线与上一条直线的交点判断上一条直线还有没有可能在某个区间成为答案,若当前直线的加入让上条直线不可能成为答案了，则上条直线出队。最后加入当前直线。
特别地，**当$X(j)$存在单调性时**，可直接查询时删除小于询问范围的头部。即可直接单调队列$O(n)$复杂度。
**当$X(j)$不存在单调性时**，头部不满足当前范围的信息不能直接删除，只能通过二分查询到对应区间。$O(nlogn)$ 

当**$X(j)$存在单调性**时代码(通过优先队列入队出队做到     $O(n)$)

```c++
constexpr int inf=2e9;
int sign(ll x) {return (x>0)-(x<0);}// 符号
struct Fraction {// 注意分数比较爆long long
    ll a,b;
    Fraction(ll a,ll b) : a(sign(a^b)*abs(a)/gcd(a,b)),b(abs(b)/gcd(a,b)) {}
    bool operator<=(const Fraction &o) const {return a*o.b<=b*o.a;}
};
const Fraction neg_inf={-inf,1};
const Fraction pos_inf={inf,1};
struct Convex_opt {
    struct Line {
        ll k,b;
        Fraction x=neg_inf;
        ll operator[](ll x) const{return k*x+b;}
        Fraction operator&(const Line &l) const {return {l.b-b,k-l.k};} // 交点横坐标
    };
    deque<Line> q;
    void update(const Line &l) {
        auto x=neg_inf;
        while(!q.empty() && (x=(l&q.back()))<=q.back().x) 
            q.pop_back();
        q.push_back({l.k,l.b,x});
    }
    ll query(ll x) {
        Fraction fx={x,1};
        while(q.size()>1 && q[1].x<=fx)
            q.pop_front();
        q.front().x=neg_inf;
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
```

当**$X(j)$不存在单调性**时代码(思路不变,优先队列不再出队,直接用二分查询对应位置    $O(nlogn)$)
```c++
vector<Line> q; // deque可直接换成vector,减小时空常数
ll query(ll x) { //原优先队列出队操作换做二分查找
    Fraction fx={x,1};
    int l=0,r=q.size(),mid;
    while(l<r) {
        mid=(l+r)/2;
        if(q[mid].x<=fx) l=mid+1;
        else r=mid;
    }
    return q[l-1][x];
}
```

### 李超线段树优化DP

该方法也不要保证自变量$X(j)$保持单调,时间复杂度:单次修改$O(log^2n)$单次查询$O(logn)$ 

```c++
constexpr int inf=2e9;
constexpr int L=1,R=1000010;// 自变量X(j)值域范围
int sign(ll x) {return (x>0)-(x<0);}// 符号: >0是1  =0是0  <0是-1
//int sign(double x) {return (x>-eps)-(x<eps);}//                    double情况
struct Segment {
    ll k,b;
    //double k,b;                                                    double情况
}seg[N];
//double f(int id,ll x)                                              double情况
ll f(int id,ll x) { 
    return seg[id].k*x+seg[id].b;
}
bool check(int pre,int now,ll x) {
    ll f1=f(pre,x),f2=f(now,x);
    return sign(f1-f2)?f1>f2:(f1==f2 && pre>now);
    //double f1=f(pre,x),f2=f(now,x);
    //return sign(f2-f1)==1?1:(sign(f2-f1)==0 && pre>now);           double情况
}
struct segtree {
    struct Node {
        int l,r;
        int id;
    };
    vector<Node> tr;
    segtree() {init();}
    void init() {tr.assign(2,Node());} // tr.reserve(5000000);
    int newNode() {
        tr.emplace_back();
        return tr.size()-1;
    }
    void add(int p,int opt) { //0---ls   1---rs
        if(!opt && !tr[p].l) {
            tr[p].l=newNode();
            tr[tr[p].l].id=tr[p].id;
        } 
        else if(opt && !tr[p].r) {
            tr[p].r=newNode();
            tr[tr[p].r].id=tr[p].id;
        }
    }
    void modify(int p,int l,int r,int x,int y,int id) {
        if(r<x || l>y) return;
        int mid=(l+r)>>1;
        if(x<=l && r<=y) {
            if(check(tr[p].id,id,mid)) swap(tr[p].id,id);
            if(check(tr[p].id,id,l) && check(tr[p].id,id,r)) return;
            if(check(tr[p].id,id,l)) add(p,0),modify(tr[p].l,l,mid,x,y,id);
            if(check(tr[p].id,id,r)) add(p,1),modify(tr[p].r,mid+1,r,x,y,id);
            return ;
        }
        if(x<=mid) add(p,0),modify(tr[p].l,l,mid,x,y,id);
        if(y>mid) add(p,1),modify(tr[p].r,mid+1,r,x,y,id);
    }
    int query(int p,int l,int r,int x) {
        if(l==x && x==r) return tr[p].id;
        else {
            int mid=(l+r)>>1,res=0;
            if(x<=mid && tr[p].l) res=query(tr[p].l,l,mid,x);
            else if(x>mid && tr[p].r) res=query(tr[p].r,mid+1,r,x);
            else res=tr[p].id;
            if(check(res,tr[p].id,x)) res=tr[p].id;// 必要
            return res;
        }
    }
    void modify(int x,int y,int id) {
        modify(1,L,R,x,y,id);
    }
    ll query(int x) {
        return f(query(1,L,R,x),x);
    }
};
//solve()
segtree tree;
seg[0]={0,inf};//维护最小值初值赋inf，维护最大值初值赋-inf
for(int i=1;i<=n;i++) {
    if(i>1) dp[i]=tree.query(h[i])+h[i]*h[i]+c;
    seg[i]={-2*h[i],dp[i]+h[i]*h[i]};
    tree.modify(L,R,i);
}
```

