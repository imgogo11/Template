int root;
bool cut_point[N],bridge[M];;
struct EBCC {
    int n;
    vector<vector<pair<int,int>>> adj;
    vector<int> stk;
    vector<int> dfn,low,col;
    int cur,cnt,edgeid,points,edges;
    EBCC() {}
    EBCC(int n) {init(n);}
    void init(int n) {
        this->n=n;
        adj.assign(n+1,{});
        dfn.assign(n+1,-1);
        low.resize(n+1);
        col.assign(n+1,-1);
        stk.clear();
        cur=cnt=edgeid=points=edges=0;
    }
    void addEdge(int u,int v) {
        adj[u].push_back({v,edgeid++});
        adj[v].push_back({u,edgeid++});
    }
    void dfs(int x,int inedge) {
        int tot=0;
        dfn[x]=low[x]=cur++;
        stk.push_back(x);
        for(auto [y,id] : adj[x]) {
            if(id==(inedge^1)) continue;
            if(dfn[y]==-1) {
                dfs(y,id);
                ++tot;
                low[x]=min(low[x],low[y]);
                if(low[y]>dfn[x] && !bridge[id/2]) {
                    edges+=1;
                    bridge[id/2]=1;
                }
                if(low[y]>=dfn[x] && !cut_point[x]) {
                    points+=1;
                    cut_point[x]=true;
                }
            }else if(col[y]==-1 && dfn[y]<dfn[x]) {
                low[x]=min(low[x],dfn[y]);
            }
        }
        if(x==root && tot<2 && cut_point[x]) {
            points-=1;
            cut_point[x]=false;
        }
        if(dfn[x]==low[x]) {
            int y;
            cnt+=1;
            do{
                y=stk.back();
                col[y]=cnt;
                stk.pop_back();
            } while(y!=x);

        }
    }
    vector<int> work() {
        for(int i=1;i<=n;i++)
            if(dfn[i]==-1) {
                root=i;
                dfs(i,-1);
            }
        return col;
    }
    int ebccnum() {return cnt;}
    int cut_points() {return points;}
    int cut_edges() {return edges;}
};