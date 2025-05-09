struct SCC {
    int n;
    vector<vector<int>> adj;
    vector<int> stk,dfn,low,col;
    int cur,cnt;
    SCC() {}
    SCC(int n) {init(n);}
    void init(int n) {
        this->n=n;
        adj.assign(n+1,{});dfn.assign(n+1,-1);col.assign(n+1,-1);
        low.resize(n+1);
        stk.clear();
        cur=cnt=0;
    }
    void addEdge(int u,int v) {adj[u].push_back(v);}
    void dfs(int x) {
        dfn[x]=low[x]=cur++;
        stk.push_back(x);
        for (int y: adj[x]) {
            if(dfn[y]==-1) {
                dfs(y);
                low[x]=min(low[x],low[y]);
            } else if(col[y]==-1) {
                low[x]=min(low[x],dfn[y]);
            }
        }
        if(dfn[x]==low[x]) {
            int y;
            cnt+=1;
            do {
                y=stk.back();
                col[y]=cnt;
                stk.pop_back();
            }while(y!=x);
        }
    }
    vector<int> work() {
        for (int i=1;i<=n;i++) if(dfn[i]==-1) dfs(i);
        return col;
    }
    int sccnum() {return cnt;}
};