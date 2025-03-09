# 预处理线性求逆元

$1^{-1}\equiv 1\pmod{p}$ (初始化1的逆元为1)
设$p=k*i+r,(1<r<i<p)$,$k=\lfloor{\frac{p}{i}}\rfloor,r=p \mod i$  
能得到$k*i+r \equiv0 \pmod{p}$ 
乘上$i^{-1},r^{-1}$得到:$k*r^{-1}+i^{-1}\equiv0 \pmod{p}$ 
$i^{-1}\equiv -k*r^{-1} \pmod{p}$ 
$i^{-1}\equiv -\lfloor{\frac{p}{i}}\rfloor*(p \mod i)^{-1} \pmod{p}$ 
$i^{-1}\equiv (p-\lfloor{\frac{p}{i}}\rfloor)*(p \mod i)^{-1} \pmod{p}$ 

```c++
inv[1] = 1;
for(int i = 2;i <= n;i++)
    inv[i] = (p - p / i) * inv[p % i] % p;
```

