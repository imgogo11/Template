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