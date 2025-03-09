# Excrt

$X \equiv x_1 \pmod{p_1} \xrightarrow{} X \mod{p_1} =x_1$ 
$X \equiv x_2 \pmod{p_2} \xrightarrow{} X \mod{p_2} =x_2$ 
$X \equiv x_3 \pmod{p_3} \xrightarrow{} X \mod{p_3} =x_3$ 
                                     $\vdots$ 
$X \equiv x_n \pmod{p_n} \xrightarrow{} X \mod{p_n} =x_n$ 
令$X=C_1+C_2+C_3+\dots+C_n$ 
同时$C_1 \mod{p_1}=x_1\;\;AND\;\;C_2 \mod{p_2}=0\;\;AND\;\;\dots\;\;AND\;\;C_n \mod{p_n}=0$ 
同时$C_2 \mod{p_2}=x_2\;\;AND\;\;C_1 \mod{p_1}=0\;\;AND\;\;\dots\;\;AND\;\;C_n \mod{p_n}=0$ 
同时$C_3 \mod{p_3}=x_3\;\;AND\;\;C_1 \mod{p_1}=0\;\;AND\;\;\dots\;\;AND\;\;C_n \mod{p_n}=0$ 
                                                                           $\vdots$ 
同时$C_n \mod{p_n}=x_n\;\;AND\;\;C_1 \mod{p_1}=0\;\;AND\;\;\dots\;\;AND\;\;C_{n-1} \mod{p_{n-1}}=0$ 
可得：
$C_1=x_1p_2p_3\dots p_n(\frac{1}{p_2p_3\dots p_n} \mod p_1)$ 
$C_2=x_2p_1p_3\dots p_n(\frac{1}{p_1p_3\dots p_n} \mod p_2)$ 
$C_3=x_3p_1p_2\dots p_n(\frac{1}{p_1p_2\dots p_n} \mod p_3)$ 
			   $\vdots$ 
$C_n=x_np_1p_2\dots p_{n-1}(\frac{1}{p_1p_2\dots p_{n-1}} \mod p_n)$ 
得到解:$X=\sum_{i=1}^{n}x_ir_i[r_i]^{-1}|_{p_i} \mod{lcm}$ 

```c++
for(int i=1;i<=n;i++) {
    exgcd(prod/a[i],a[i],x,y);
    x%=lcm;
    if(x<0) x+=lcm;
    Add(sum,mul(mul(b[i],prod/a[i],lcm),x,lcm),lcm);
}
```

