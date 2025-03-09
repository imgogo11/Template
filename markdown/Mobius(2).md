### Mobius(2)

下面式子默认$n\le m$ ,$(i,j)$指的是$gcd(i,j)$ 
$$
~~~~~\sum_{i=1}^{n}\sum_{j=1}^{m}[(i,j)=1] \\
~~~~~~~~~~~~~~~~~~~~~~~~~~~=\sum_{i=1}^{n}\sum_{j=1}^{m}\sum_{d|(i,j)}\mu(d)~~~~~~~~~~(e=\mu*I) \\
=\sum_{d=1}^{n}\mu(d)\sum_{d|i}^{n}\sum_{d|j}^{m}1 \\
=\sum_{d=1}^{n}\mu(d)\lfloor \frac{n}{d} \rfloor\lfloor \frac{m}{d} \rfloor \\
$$
同理可得$\sum_{i=1}^{n}\sum_{j=1}^{m}[(i,j)=k]~~=~~\sum_{i=1}^{\lfloor \frac{n}{k} \rfloor}\sum_{j=1}^{\lfloor \frac{m}{k} \rfloor}[(i,j)=1]$ 
对于$n=m,\sum_{i=1}^{n}\sum_{j=1}^{n}[(i,j)=1]=(\sum_{i=1}^{n}~~2\sum_{j=1}^{i}[(i,j)=1])-1=2\sum_{i=1}^n \varphi(i) - 1$ 
($i=j=1$)重复贡献，所以最后需要$-1$ 
$$
~~~~~\sum_{i=1}^{n}\sum_{j=1}^{m}(i,j) \\
~~~~~~~~~~~~~~~~~~~~~~~~~~~=\sum_{i=1}^{n}\sum_{j=1}^{m}\sum_{d|(i,j)}\varphi(d)~~~~~~~~~~(id=\varphi*I) \\
=\sum_{d=1}^{n}\varphi(d)\sum_{d|i}^{n}\sum_{d|j}^{m}1 \\
=\sum_{d=1}^{n}\varphi(d)\lfloor \frac{n}{d} \rfloor\lfloor \frac{m}{d} \rfloor \\
$$
对于$\sum_{i=1}^{n}\sum_{j=1}^{m}f((i,j))$这一类问题，都可根据$Dirichlet$卷积类似下式的形式
$f=1*g \to g=f*\mu$      推出     $\sum_{i=1}^{n}\sum_{j=1}^{m}\sum_{d|(i,j)}g(d)$ 
例如第二个样例也可以这样推$\sum_{i=1}^n\sum_{j=1}^m\sum_{d|(i,j)}\mu(d)id(\frac{(i,j)}{d})=\sum_{i=1}^{n}\sum_{j=1}^{m}\sum_{d|(i,j)}\varphi(d)$ 
求$\sum_{i=1}^n\sum_{j=1}^m[(i,j)=k]$代码

```c++
ll cal(int n,int m,int k) {
    if(n>m) swap(n,m);
    n/=k,m/=k;
    ll ans=0;
    for(int l=1;l<=n;l++) {
        int r=min(n/(n/l),m/(m/l));
        ans+=1LL*(pre[r]-pre[l-1])*(n/l)*(m/l);
        l=r;
    }
    return ans;
}
```

对于$\sum_{i=a}^b\sum_{j=c}^d$，容斥转化为$\sum_{i=1}^b\sum_{j=1}^d-\sum_{i=1}^{a-1}\sum_{j=1}^d-\sum_{i=1}^b\sum_{j=1}^{c-1}+\sum_{i=1}^{a-1}\sum_{j=1}^{c-1}$ 