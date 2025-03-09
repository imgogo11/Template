int vis[N],phi[N],p[N],mu[N],cnt;
void sieve(int n) {
    phi[1]=mu[1]=1;
    for(int i=2;i<=n;i++) {
        if(!vis[i]) vis[i]=i,p[++cnt]=i,phi[i]=i-1,mu[i]=-1;
        for(int j=1;p[j]<=n/i;j++) {
            vis[p[j]*i]=p[j];
            if(i%p[j]==0) {
                phi[i*p[j]]=phi[i]*p[j];
                mu[i*p[j]]=0;
                break;
            }
            phi[i*p[j]]=phi[i]*phi[p[j]];
            mu[i*p[j]]=-mu[i];
        }
    }
}