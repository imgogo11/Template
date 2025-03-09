template<class T>struct MaxFlow {
    struct _Edge {
        int to;
        T cap;
        _Edge(int to, T cap) : to(to), cap(cap) {}
    };
    int n;
    vector<_Edge> e;
    vector<vector<int>> g;
    vector<int> cur, h;
    MaxFlow() {}
    MaxFlow(int n) {init(n);}
    void init(int n) {
        this->n = n;
        e.clear();
        g.assign(n+1, {});
        cur.resize(n+1);
        h.resize(n+1);
    }
    void addEdge(int u, int v, T c) {
        g[u].push_back(e.size());
        e.emplace_back(v, c);
        g[v].push_back(e.size());
        e.emplace_back(u, 0);
    }
    bool bfs(int s, int t) {
        h.assign(n+1, -1);h[s]=0;
        queue<int> q;q.push(s);
        while(!q.empty()) {
            const int u = q.front();
            q.pop();
            for(int i : g[u]) {
                auto [v, c] = e[i];
                if(c > 0 && h[v] == -1) {
                    h[v] = h[u] + 1;
                    if(v == t) return true;
                    q.push(v);
                }
            }
        }
        return false;
    }
    T dfs(int u, int t, T f) {
        if(u == t) return f;
        auto r = f;
        for(int &i = cur[u]; i < int(g[u].size()); ++i) {
            const int j = g[u][i];
            auto [v, c] = e[j];
            if(c > 0 && h[v] == h[u] + 1) {
                auto a = dfs(v, t, min(r, c));
                e[j].cap -= a;
                e[j ^ 1].cap += a;
                r -= a;
                if(r == 0) return f;
            }
        }
        return f - r;
    }
    T flow(int s, int t) {
        T ans = 0;
        while(bfs(s, t)) {
            cur.assign(n+1, 0);
            ans += dfs(s, t, numeric_limits<T>::max());
        }
        return ans;
    }
    vector<bool> minCut() {// 1代表源点集合S,0代表汇点集合T
        vector<bool> c(n+1);
        for(int i = 1; i <= n; i++)
            c[i] = (h[i] != -1);
        return c;
    }
    struct Edge {
        int from,to;
        T cap,flow;
    };
    vector<Edge> edges() {
        vector<Edge> a;
        for(int i = 0; i < e.size(); i += 2) {
            Edge x;
            x.from = e[i + 1].to;
            x.to = e[i].to;
            x.cap = e[i].cap + e[i + 1].cap;
            x.flow = e[i + 1].cap;
            a.push_back(x);
        }
        return a;
    }
};
using Flow = MaxFlow<long long>;