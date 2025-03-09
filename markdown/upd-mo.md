### 带修莫队

普通莫队,先按左端点块再按左端点块奇升偶降(常数优化r端点移动次数)
块长$\sqrt n$时,总复杂度$O((n+q)\sqrt n)~~~~~~~~~~~~~~$块长$\frac{n}{\sqrt q}$时,总复杂度$O(n\sqrt q)$ 
带修莫队,视$n~~m$同阶,取$B=n^{\frac{2}{3}}$,时间复杂度达到$O(n^{\frac{5}{3}})$ 

```c++
constexpr int N = 1e6 + 10;
struct BLK {
    int B,n;
    vector<int> id;
    vector<int> pos; 
    BLK() : B{}, n{}, id{} {}
    BLK(int n) :BLK() {init(n);}
    void init(int n) {
        this->n=n;
        this->B=(int)pow(n,2.0/3);
        id.resize(n+1);
        pos.assign(N,0);
        for(int i=1;i<=n;i++)
            id[i]=(i-1)/B+1;
    }
    bool del_l(int &x,int val) {
        x+=1;
        bool ischange=false;
        pos[val]-=1;
        if(!pos[val]) ischange=true;
        return ischange;
    }
    bool del_r(int &x,int val) {
        x-=1;
        bool ischange=false;
        pos[val]-=1;
        if(!pos[val]) ischange=true;
        return ischange;
    }
    int del_t(int &x,int &val1,int &val2) {
        x-=1;
        int ischange=0;
        if(val1==val2) return ischange;
        pos[val1]-=1,pos[val2]+=1;
        if(pos[val1]>0 && pos[val2]==1) ischange=1;
        else if(pos[val1]==0 && pos[val2]>1) ischange=-1;
        swap(val1,val2);
        return ischange;
    }
    bool add_l(int &x,int val) {
        x-=1;
        bool ischange=false;
        if(!pos[val]) ischange=true;
        pos[val]+=1;
        return ischange;
    }
    bool add_r(int &x,int val) {
        x+=1;
        bool ischange=false;
        if(!pos[val]) ischange=true;
        pos[val]+=1;
        return ischange;
    }
    int add_t(int &x,int &val1,int &val2) {
        x+=1;
        int ischange=0;
        if(val1==val2) return ischange;
        pos[val1]-=1,pos[val2]+=1;
        if(pos[val1]>0 && pos[val2]==1) ischange=1;
        else if(pos[val1]==0 && pos[val2]>1) ischange=-1;
        swap(val1,val2);
        return ischange;
    }
};
void solve() {
    int n,q,time=0,tot=0,L,R;
    char op;
    cin>>n>>q;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++) cin>>a[i];
    BLK B(n);
    vector<int> l(q+1),r(q+1),t(q+1),p(q+1),after(q+1);
    for(int i=1;i<=q;i++) {
        cin>>op>>L>>R;
        if(op=='Q') {
            t[++tot]=time;
            l[tot]=L,r[tot]=R;
        }
        else {
            time+=1;
            p[time]=L,after[time]=R;
        }
    }
    vector<int> ans(tot+1),idx(tot+1);
    iota(idx.begin(),idx.end(),0);
    sort(idx.begin(),idx.end(),[&](int R1,int R2){
        if(B.id[l[R1]]!=B.id[l[R2]])
            return B.id[l[R1]]<B.id[l[R2]];
        if(B.id[r[R1]]!=B.id[r[R2]])
            return B.id[r[R1]]<B.id[r[R2]];
        return t[R1]<t[R2];
    });
    int nl=1,nr=0,nt=0,cnt=0;
    for(int i=1;i<=tot;i++) {
        int now=idx[i];
        while(nr<n && nr<r[now]) {
            if(B.add_r(nr,a[nr+1]))
                cnt+=1;
        }
        while(nl>1 && nl>l[now]) {
            if(B.add_l(nl,a[nl-1]))
                cnt+=1;
        }
        while(nl<=n && nl<l[now]) {
            if(B.del_l(nl,a[nl]))
                cnt-=1;
        }
        while(nr>=1 && nr>r[now]) {
            if(B.del_r(nr,a[nr]))
                cnt-=1;
        }
        while(nt<time && nt<t[now]) {
            if(p[nt+1]>nr || p[nt+1]<nl)
                swap(a[p[nt+1]],after[nt+1]),nt+=1;
            else
                cnt+=B.add_t(nt,a[p[nt+1]],after[nt+1]);
        }
        while(nt>=1 && nt>t[now]) {
            if(p[nt]>nr || p[nt]<nl)
                swap(a[p[nt]],after[nt]),nt-=1;
            else
                cnt+=B.del_t(nt,a[p[nt]],after[nt]);
        }
        ans[now]=cnt;
    }
    for(int i=1;i<=tot;i++) cout<<ans[i]<<"\n";
}
```

