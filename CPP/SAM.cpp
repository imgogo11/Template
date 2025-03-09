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