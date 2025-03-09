### PAM

对于一个字符串s,它的本质不同回文子串个数最多只有|s|个
构造回文树时间复杂度$O(|s|)$
**fail指针(link)**指向子串的**最长回文真后缀**
suff代表的是,前缀的**最长回文后缀**,($pam.len(suff)$即为以当前位置结尾最长回文子串长度)
0号点为奇根,1号点为偶根,偶根fail指向奇根
每一个Node代表了一种状态,**len**为该状态的回文子串长度,**link**指向该回文子串的最长回文真后缀,**cnt**表示该状态回文子串个数

```c++
struct PAM {
    static constexpr int ALPHABET_SIZE = 26;
    struct Node {
        int len,link,cnt;
        array<int, ALPHABET_SIZE> next;
        Node() : len{}, link{}, cnt{}, next{} {}
    };
    vector<Node> t;
    int suff;
    string s;
    PAM() {init();}
    void init() {
        t.assign(2, Node());
        t[0].len = -1;
        suff = 1;
        s.clear();
    }
    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }
    bool add(char c) {
        int pos = s.size();
        s += c;
        int let = c - 'a';
        int cur = suff, curlen = 0;
        while(true) {//getfail
            curlen = t[cur].len;
            if(pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos]) {
                break;
            }
            cur = t[cur].link;
        }
        if(t[cur].next[let]) {
            suff = t[cur].next[let];
            return false;
        }
        int num = newNode();
        suff = num;
        t[num].len = t[cur].len + 2;
        t[cur].next[let] = num;
        if(t[num].len == 1) {
            t[num].link = 1;
            t[num].cnt = 1;
            return true;
        }
        while(true) {//getfail
            cur = t[cur].link;
            curlen = t[cur].len;
            if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos]) {
                t[num].link = t[cur].next[let];
                break;
            }
        }
        t[num].cnt = 1 + t[t[num].link].cnt;
        return true;
    }
    int next(int p, int x) {return t[p].next[x];}
    int link(int p) {return t[p].link;}
    int len(int p) {return t[p].len;}
    int cnt(int p) {return t[p].cnt;}
    int size() {return t.size();}
};
```

fail边建树能得到每种回文子串的出现次数,f[u]代表回文子串u出现的次数(u为状态编号)
```c++
for(char ch: s)
{
    pam.add(ch);
    ends.push_back(pam.suff);
}
vector<int> f(pam.size());
for(int v: ends)
    f[v]++;
vector adj(pam.size(),vector<int>());
for(int i=2;i<pam.size();i++)
    adj[pam.link(i)].push_back(i);
ll ans=0;
auto dfs=[&](auto &&dfs,int u)->void
{
    for(int v: adj[u])
    {
        dfs(dfs,v);
        f[u]+=f[v];
    }
    ans=max(ans,1LL*pam.len(u)*pam.len(u)*f[u]);
};
dfs(dfs,1);
```



