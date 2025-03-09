template<typename T>struct RMQ {
    vector<vector<T>> f;
    int n,k;
    RMQ(){}
    RMQ(int n){init(n);}
    T op(T A,T B) {return gcd(A,B);}
    void init(int n) {
        this->n=n;
        this->k=__lg(n);
        f.assign(k+1,vector<T>(n+1));
    }
    void work(){
        for(int i=1;i<=k;i++)
            for(int j=1;j<=n-(1<<i)+1;j++)
                f[i][j]=op(f[i-1][j],f[i-1][j+(1<<(i-1))]);
    }
    T query(int l,int r) {
        if(l>r) return 0;
        int len=__lg(r-l+1);
        return op(f[len][l],f[len][r-(1<<len)+1]);
    }
};