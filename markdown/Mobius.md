### Mobius

#### 积性函数

$$
\left\{
\begin{array}{l}
f(ab)=f(a)f(b),~ \forall(a,b)=1~~~~(积性函数)\\
f(ab)=f(a)f(b),~ \forall ~a,b~~~~~~~~~~~~~~(完全积性函数)\\
\end{array}
\right.
$$

##### 莫比乌斯函数

$$
\left\{
\begin{array}{l}
\mu(n)=1 ~~~~~~~~~~~(n=1)\\
\mu(n)=0 ~~~~~~~~~~~(n存在平方因子)\\
\mu(n)=(-1)^k ~~~(k为质因子个数)\\
\end{array}
\right.
$$

##### 欧拉函数                       $\varphi(n)= \sum_{d=1}^{n} [gcd(d,n)=1]=n\sum_{p|n}(1-\frac{1}{p})~~~~~(p是n的所有质因子)$ 

##### 因子和函数                   $\sigma(n)=\sum_{d|n} d$ 

##### 因子个数函数               $d(n)=\sum_{d|n} 1$            $d(xy)=\sum_{d|xy}1=\sum_{i|x}\sum_{j|y}[(i,j)=1]$ 

##### 恒等函数                       $id(n)=n$ 

##### 常数函数                       $I(n)=1$ 

##### 单位元函数                   $\epsilon[n]=[n=1]$ 

#### 反演重要结论

1. ​    $\epsilon=I*\mu~~~~~~~~~~~~~~~~\epsilon(n)=\sum_{d|n} \,\,\mu(d)$  
2. ​    $id=I*\varphi~~~~~~~~~~~~~~n=\sum_{d|n} \varphi(d)$ 
3. ​    $\sigma=I*id~~~~~~~~~~~~~~\sigma(n)=\sum_{d|n} d$ 
4. ​    $\varphi=\mu*id~~~~~~~~~~~~~\varphi(n)=\sum_{d|n} \mu(d)id(\frac{n}{d})$  
5. ​    $d=I*I~~~~~~~~~~~~~~~d(n)=\sum_{d|n} 1$ 

#### Dirichlet卷积

形式：$f(n)=\sum_{d|n}g(d) \Leftrightarrow g(n)=\sum\mu(\frac{n}{d})f(d)$ 
$~~~~~~~~~~~~~~~~~~~~~~~~f=g * 1 \Leftrightarrow g=\mu * f$ 
结论：任一积性函数一定满足$f(1)=1$ 
若$f(x)$和$g(x)$均为积性函数则$h(x)=f(x^p)~~~~~h(x)=f^p(x)~~~~~h(x)=f(x)g(x)~~~~~h(x)=\sum_{d|x}f(d)g(\frac{x}{d})$均为积性函数
