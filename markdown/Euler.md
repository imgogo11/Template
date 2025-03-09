### 欧拉通路

有向图：图连通，有一个顶点出度大入度1，有一个顶点入度大出度1，其余都是出度=入度。
无向图：图连通，只有两个顶点是奇数度，其余都是偶数度的。

### 欧拉回路

有向图：图连通，所有的顶点出度=入度。
无向图：图连通，所有顶点都是偶数度。



### Euler_sieve

$phi$表示每个数的欧拉函数值，$mu$表示每个数的莫比乌斯函数值
暴力求欧拉函数根据公式$\varphi(a*b)=\varphi((a*b)/gcd(a,b))*gcd(a,b)$ 
$p$存储了所有的质数下标从1开始,$cnt$代表质数个数,$vis$为每个数的最小质因子，注意$1$的$vis$为$0$ 
$vis[x]=x$说明x为质数

```c++
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
```

枚举质数需要条件$i<=cnt$，否则有可能会枚举到越界

```c++
for(int i=1;p[i]<=10000000 && i<=cnt;i++) {

}
```

