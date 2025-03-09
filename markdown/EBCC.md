### EBCC

对于一个无向图中的极大边双连通的子图，我们称这个**子图为**一个 **边双连通分量**。
**边双连通分量**(无论删去哪条边都不能使他们不连通)
**点双连通分量**(无论删去哪条点都不能使他们不连通)
points为割点数,cut_point为true代表是割点(点下标从1开始)
edges为割边数,bridge为true代表是割边(边下标从0开始)
有割点不一定有割边(桥),有割边(桥)一定存在割点
同一个连通分量内的点都标了相同的col

```c++
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
```

