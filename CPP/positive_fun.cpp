int vis[N],p[N],pe[N],f[N],cnt;
void sieve(int n) {
    for(int i=2;i<=n;i++) {
        if(!vis[i]) vis[i]=i,p[++cnt]=i,pe[i]=i;
        for(int j=1;p[j]<=n/i;j++) {
            vis[p[j]*i]=p[j];
            if(i%p[j]==0) {
                pe[i*p[j]]=pe[i]*p[j];
                break;
            }
            pe[i*p[j]]=p[j];
        }
    }
}
void cal(int n,function<void(int)> comp) {//   auto &&comp
    f[1]=1;
    for(int i=2;i<=n;i++) {
        if(i==pe[i]) comp(i);
        else f[i]=f[pe[i]]*f[i/pe[i]];
    }
}
cal(100000,[&](int x) {f[x]=(vis[x]==x?-1:0);});//mu(莫比乌斯函数)
cal(100000,[&](int x) {f[x]=x/vis[x]*(vis[x]-1);});//phi(欧拉函数)
cal(100000,[&](int x) {f[x]=f[x/vis[x]]+x;});//sigma(因子和函数)
cal(100000,[&](int x) {f[x]=(vis[x]?0:-1);});//d(因子个数函数)