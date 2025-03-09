# fhq-treap

```c++
mt19937 rng{chrono::steady_clock::now().time_since_epoch().count()};
int root,T1,T2,T3,cnt;
struct FHQ
{
    struct Node {
        int ls,rs,key,sz,val;
    };
    vector<Node> tr;
    FHQ(){}
    FHQ(int n){init(n);}
    void init(int n) {
        tr.resize(n+10);
        root=T1=T2=T3=cnt=0;
    }
    int newNode(int v) {
        tr[++cnt]={0,0,(int)rng(),1,v};
        return cnt;
    }
    void pushup(Node &u,Node &ls,Node &rs) {
        u.sz=ls.sz+rs.sz+1;
    }
    void pushup(int p){pushup(tr[p],tr[tr[p].ls],tr[tr[p].rs]);}
    void split(int u,int v,int &x,int &y) {
        if(!u) {
            x = y = 0;
            return;
        }
        if(tr[u].val>v){
            y=u;
            split(tr[u].ls,v,x,tr[u].ls);
        }
        else{
            x=u;
            split(tr[u].rs,v,tr[u].rs,y);
        }
        pushup(u);
    }
    void split_rank(int u,int v,int &x,int &y) {
        if(!u) {
            x = y = 0;
            return;
        }
        int tmp=tr[tr[u].ls].sz+1;
        if(tmp==v) {
            x=u;
            y=tr[u].rs;
            tr[u].rs=0;
        }
        else if(tmp>v) {
            y=u;
            split_rank(tr[u].ls,v,x,tr[u].ls);
        }
        else {
            x=u;
            split_rank(tr[u].rs,v-tmp,tr[u].rs,y);
        }
        pushup(u);
    }
    int merge(int x,int y) {
        if(!x || !y) return x + y;
        if(tr[x].key>tr[y].key) {
            tr[x].rs=merge(tr[x].rs,y);
            pushup(x);
            return x;
        }
        else {
            tr[y].ls=merge(x,tr[y].ls);
            pushup(y);
            return y;
        }
    }
    void insert(int v) {
        split(root,v,T1,T2);
        root=merge(merge(T1,newNode(v)),T2);
    }
    void erase(int v) {
        split(root,v,T1,T2);
        split(T1,v-1,T1,T3);
        T3=merge(tr[T3].ls,tr[T3].rs);
        root=merge(merge(T1,T3),T2);
    }
    int rank(int x) {
        split(root,x-1,T1,T2);
        int res=tr[T1].sz+1;
        root=merge(T1,T2);
        return res;
    }
    int kth(int k) {
        int u=root;
        while(u) {
            int tmp=tr[tr[u].ls].sz+1;
            if(tmp==k) break;
            else if(k<tmp) u=tr[u].ls;
            else k-=tmp,u=tr[u].rs;
        }
        return tr[u].val;
    }
    int find_pre(int u,int v) {
        if(u==0) return -INF;
        if(tr[u].val<v) {
            int res=find_pre(tr[u].rs,v);
            return res==-INF?tr[u].val:res;
        }
        else {
            return find_pre(tr[u].ls,v);
        }
    }
    int find_next(int u,int v) {
        if(u==0) return INF;
        if(tr[u].val>v) {
            int res=find_next(tr[u].ls,v);
            return res==INF?tr[u].val:res;
        }
        else {
            return find_next(tr[u].rs,v);
        }
    }
    int sz(int u) {return tr[u].sz;}
    int val(int u) {return tr[u].val;}
};
```

