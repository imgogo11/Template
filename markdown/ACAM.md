### ACAM

时间复杂度为$O(\sum\vert S_i \vert+n\vert\sum\vert+\vert S\vert)$
$\vert S_i \vert$为模式串长度,$\vert S\vert$为文本串长度,$\vert\sum\vert$为字符集大小，一般为26
query函数返回每个模式串在文本串中的出现次数,模式串下标从0开始

```c++
struct ACAM {
    static constexpr int ALPHABET = 26;
    struct Node {
        int len,link;
        array<int, ALPHABET> next;
        Node() : len{}, link{}, next{} {}
    };
    vector<Node> t;
    vector<int> nodes,end;
    ACAM() {init();}
    void init() {
        t.assign(2, Node());
        nodes.clear();
        end.clear();
        t[0].next.fill(1);
        t[0].len = -1;
    }
    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }
    int add(const string &a) {
        int p = 1;
        for (char c : a) {
            int x = c - 'a';
            if (t[p].next[x] == 0) {
                t[p].next[x] = newNode();
                t[t[p].next[x]].len = t[p].len + 1;
            }
            p = t[p].next[x];
        }
        end.push_back(p);
        return p;
    }
    void work() {
        queue<int> q;
        q.push(1);
        while (!q.empty()) {
            int x = q.front();
            nodes.push_back(x);
            q.pop();
            for (int i = 0; i < ALPHABET; i++) {
                if (t[x].next[i] == 0) {
                    t[x].next[i] = t[t[x].link].next[i];
                } else {
                    t[t[x].next[i]].link = t[t[x].link].next[i];
                    q.push(t[x].next[i]);
                }
            }
        }
    }
    vector<int> query(const string &s) {
        int p=1;
        vector<int> f(t.size()+1);
        for(auto c: s) {
            p=t[p].next[c-'a'];
            f[p]+=1;
        }
        for(int i=nodes.size()-1;i>=0;i--) {
            int x=nodes[i];
            f[t[x].link]+=f[x];
        }
        vector<int> cnt(end.size());
        for(int i=0;i<end.size();i++)
            cnt[i]=f[end[i]];
        return cnt;
    }
    int next(int p,int x) {return t[p].next[x];}
    int link(int p) {return t[p].link;}
    int len(int p) {return t[p].len;}
    int size() {return t.size();}
    int number() {return end.size();}
};
```

---

求文本串中出现的模式串个数(小常数写法)

```c++
AhoCorasick aho;
vector<int> isEnd(N);
for(int i=1;i<=n;i++) {
    cin>>s;
    int p=aho.add(s);
    isEnd[p]+=1;
}
aho.work();
cin>>s;
int p=1;
for(auto c: s) {
    p=aho.next(p,c-'a');
    for(int i=p;i>1 && isEnd[i]!=-1;i=aho.link(i)) {
        ans+=isEnd[i];
        isEnd[i]=-1;
    }
}//cout<<ans<<"\n";
```

