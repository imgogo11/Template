### SAM

构建时间复杂度$O(n)$,用法和pam和acam类似
一个SAM最多**2n-1个节点,3n-4条转移边**
每个节点代表了$t[p].len-t[t[p].link]$个子串,且每个节点子串各不相同
一个状态代表一个endpos等价类,len为该等价类中最长串长度
(**aababc**中**b**和**ab**的endpos都是**{3,5}**)

```c++
struct SAM {
    static constexpr int ALPHABET_SIZE = 26;
    struct Node {
        int len,link;
        array<int, ALPHABET_SIZE> next;
        Node() : len{}, link{}, next{} {}
    };
    vector<Node> t;
    SAM() {init();}
    void init() {
        t.reserve(2000000);//预先reserver所有节点两倍,防止vector扩容爆空间
        t.assign(2, Node());
        t[0].next.fill(1);
        t[0].len = -1;
    }
    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }
    int extend(int p, int c) {
        if(t[p].next[c]) {
            int q = t[p].next[c];
            if(t[q].len == t[p].len + 1) {
                return q;
            }
            int r = newNode();
            t[r].len = t[p].len + 1;
            t[r].next = t[q].next;
            t[r].link = t[q].link;
            t[q].link = r;
            while(t[p].next[c] == q) {
                t[p].next[c] = r;
                p = t[p].link;
            }
            return r;
        }
        int cur = newNode();
        t[cur].len = t[p].len + 1;
        while (!t[p].next[c]) {
            t[p].next[c] = cur;
            p = t[p].link;
        }
        t[cur].link = extend(p, c);
        return cur;
    }
    int lcp(const string &s)
    {
        int len=0,p=1,ans=0;
        for(auto c : s) {
            c -= 'a';
            while(p != 1 && t[p].next[c] == 0)
                p=t[p].link,len=t[p].len;
            if(t[p].next[c]) p=t[p].next[c],len++;
            if(len > ans) ans=len;
        }
        return ans;
    }
    int next(int p, int x) {return t[p].next[x];}
    int link(int p) {return t[p].link;}
    int len(int p) {return t[p].len;}
    int size() {return t.size();}
};
```

功能:1. p是否在s中出现(从1号节点按p的字符在SAM上转移,同理能求最长前缀)
	 2.s的最小表示法(重复s后建出SAM,从1号节点走|s|步)
	 3.s和p的最长公共子串(lcp函数)

---

fail边建树,vector<int> f表示该状态出现次数

```c++
int p=1;
for(char ch: s)
{
    p=sam.extend(p,ch-'a');
    ends.push_back(p);
}
vector<int> f(sam.size());
for(int v: ends)
    f[v]++;
vector adj(sam.size(),vector<int>());
for(int i=2;i<sam.size();i++)
    adj[sam.link(i)].push_back(i);
auto dfs=[&](auto &&dfs,int u)->void
{
    for(int v: adj[u])
    {
        dfs(dfs,v);
        f[u]+=f[v];
    }
};
dfs(dfs,1);
```

#### GSAM(广义后缀自动机)

在多个字符串上建立后缀自动机,可求n个字符串所有本质不同子串个数
```c++
for(int i=1;i<=n;i++)
{
    string s;
    cin>>s;
    int p=1;
    for(char ch: s)
        p=sam.extend(p,ch-'a');
}
for(int i=2;i<sam.size();i++)
    ans+=sam.len(i)-sam.len(sam.link(i));
```

功能:1. n个字符串所有本质不同子串数

2. n字符串最长公共子串(某个状态在n个字符串中都有,找len最长的那个)

