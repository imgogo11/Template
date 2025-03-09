### PBDS

加第二维是为了分离相同的数

```c++
#include <bits/extc++.h>
using namespace __gnu_cxx;
using namespace __gnu_pbds;
using pii = pair<int, int>;
using Tree = tree<pii,null_type,less<pii>,rb_tree_tag,tree_order_statistics_node_update>;
constexpr int INF = 0x3f3f3f3f;
Tree st;
int Rank(pii x)
{return st.order_of_key(x)+1;}
pii kth_value(int k)
{
    auto it=st.find_by_order(k-1);
    if(it!=st.end()) return *it;
    return {INF,0};
}
void solve()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        int op,x;
        cin>>op>>x;
        if(op==1) st.insert({x,i});
        else if(op==2) st.erase(st.lower_bound({x,0}));
        else if(op==3) cout<<Rank({x,0})<<"\n";
        else if(op==4) cout<<kth_value(x).first<<"\n";
        else if(op==5) cout<<(--st.lower_bound({x,0}))->first<<"\n";
        else if(op==6) cout<<(st.upper_bound({x,INF}))->first<<"\n";
    }
}
```

