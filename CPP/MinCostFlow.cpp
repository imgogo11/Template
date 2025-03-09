template<class T>struct MinCostFlow {
    struct _Edge {
        int to;
        T cap,cost;
        _Edge(int to_, T cap_, T cost_) : to(to_), cap(cap_), cost(cost_) {}
    };
    int n;
    vector<_Edge> e;
    vector<vector<int>> g;
    vector<T> h, dis;
    vector<int> pre;
    bool dijkstra(int s, int t) {
        dis.assign(n+1, numeric_limits<T>::max());
        pre.assign(n+1, -1);
        priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> q;
        dis[s] = 0;
        q.emplace(0, s);
        while(!q.empty()) {
            T d = q.top().first;
            int u = q.top().second;
            q.pop();
            if(dis[u] != d) {//不同于普通dij
                continue;
            }
            for(int i : g[u]) {
                int v = e[i].to;
                T cap = e[i].cap;
                T cost = e[i].cost;
                if(cap > 0 && dis[v] > d + h[u] - h[v] + cost) {
                    dis[v] = d + h[u] - h[v] + cost;
                    pre[v] = i;
                    q.emplace(dis[v], v);
                }
            }
        }
        return dis[t] != numeric_limits<T>::max();
    }
    bool spfa(int s, int t) {
        dis.assign(n+1, numeric_limits<T>::max());
        pre.assign(n+1, -1);
        vector<bool> vis(n+1);
        queue<int> q;
        dis[s] = 0;
        q.push(s);
        vis[s]=true;
        while(!q.empty())
        {
            int u=q.front();
            q.pop();
            vis[u]=false;
            for(int i : g[u]) {
                int v = e[i].to;
                T cap = e[i].cap;
                T cost = e[i].cost;
                if(cap > 0 && dis[v] > dis[u] + cost) {
                    dis[v] = dis[u] + cost;
                    pre[v] = i;
                    if(vis[v]==false) q.push(v),vis[v]=true;
                }
            }
        }
        return dis[t] != numeric_limits<T>::max();
    }
    MinCostFlow() {}
    MinCostFlow(int n_) {init(n_);}
    void init(int n_) {
        n = n_;
        e.clear();
        g.assign(n+1, {});
    }
    void addEdge(int u, int v, T cap, T cost) {
        g[u].push_back(e.size());
        e.emplace_back(v, cap, cost);
        g[v].push_back(e.size());
        e.emplace_back(u, 0, -cost);
    }
    pair<T, T> flow(int s, int t) {
        T flow = 0;
        T cost = 0;
        h.assign(n+1, 0);
        for(bool flag=0;flag?dijkstra(s,t):(flag=1,spfa(s,t));) {
            for(int i = 1; i <= n; ++i) {
                h[i] += dis[i];
            }
            T aug = numeric_limits<int>::max();
            for(int i = t; i != s; i = e[pre[i] ^ 1].to) {
                aug = min(aug, e[pre[i]].cap);
            }
            for(int i = t; i != s; i = e[pre[i] ^ 1].to) {
                cost += e[pre[i]].cost * aug;
                e[pre[i]].cap -= aug;
                e[pre[i] ^ 1].cap += aug;
            }
            flow += aug;
            // cost += aug * h[t];//(若全用dijkstra求最短路)
        }
        return make_pair(flow, cost);
    }
    struct Edge {
        int from,to;
        T cap,cost,flow;
    };
    vector<Edge> edges() {
        vector<Edge> a;
        for(int i = 0; i < e.size(); i += 2) {
            Edge x;
            x.from = e[i + 1].to;   x.to = e[i].to;
            x.cap = e[i].cap + e[i + 1].cap;
            x.cost = e[i].cost;   x.flow = e[i + 1].cap;
            a.push_back(x);
        }
        return a;
    }
};
using Flow = MinCostFlow<long long>;