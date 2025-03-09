### FFT

什么是卷积，连续形式：$(f*g)(n)=\int_{-\infty}^{\infty}f(\tau)g(n-\tau)d\tau$ 

​		       离散形式 ：$(f*g)(n)=\sum_{\tau=-\infty}^{\infty}f(\tau)g(n-\tau)$ 

思想：任一d阶多项式都由d+1个点唯一确定（例如$y=kx+b$由不同的两点唯一确定）
对于d阶$f$和d阶$g$相乘后得到$2d$阶$f*g$，朴素展开后合并同类项复杂度为$O(n^2)$
但是通过值表示法角度考虑$f*g$只需由$2d+1$个点表示
$A(x)=x^2+2x+1~~~~~~~~~~~~~~~~~~~~[(-2,1),(-1,0),(0,1),(1,4),(2,9)]$  

$B(x)=x^2-2x+1~~~~~~~~~~~~~~~~~~~~[(-2,9),(-1,4),(0,1),(1,0),(2,1)]$ 

$C(x)=x^4-2x^2+1~~~~~~~~~~~~~~~~~~[(-2,9),(-1,0),(0,1),(1,0),(2,9)]$ 

此时，若是我们能每次算出一个点，那么复杂度就变成了$O(d)$ 
若每次任意固定一个x，带入计算为$O(d)$，共$2d+1$个点，复杂度变回了$O(d^2)$ 
考虑奇函数偶函数性质$f(x)=-f(-x)$和$f(x)=f(-x)$ 
同时$P(x)=P_e(x^2)+xP_o(x^2)$ 
例如，$P(x)=3x^5+2x^4+x^3+7x^2+5x+1=(2x^4+7x^2+1)+x(3x^4+x^2+5)$ 
$P(x_i)=P_e(x_i^2)+x_iP_o(x_i^2)~~~~~~~~~~~~P(-x_i)=P_e(x_i^2)-x_iP_o(x_i^2)$ 
接下来通过分治思想，向下递归，最多递归约$log(2d)$层 
以下为非递归，倍增优化版

```c++
using cp=complex<double>;
int rev[N],bit,tot,res[N];//N要开多项式最高项和的两倍，即2(n+m)
cp a[N],b[N];
void fft(cp a[],int inv) {
    for(int i=0;i<tot;i++) if (i<rev[i]) swap(a[i],a[rev[i]]);
    for(int k=1;k<tot;k*=2) {
        auto w1=cp(cos(PI/k),inv*sin(PI/k));
        for(int i=0;i<tot;i+=k*2) {
            auto wk=cp(1,0);
            for(int j=0;j<k;j++,wk=wk*w1) {
                auto x=a[i+j],y=wk*a[i+j+k];
                a[i+j]=x+y,a[i+j+k]=x-y;
            }
        }
    }
}
void mul(int n,int m) {
    while((1<<bit)<n+m+1) bit++;
    tot=1<<bit;
    for(int i=0;i<tot;i++)
        rev[i]=(rev[i>>1]>>1) | ((i&1)<<(bit-1));
    fft(a,1),fft(b,1);
    for(int i=0;i<tot;i++) a[i]=a[i]*b[i];
    fft(a,-1);
    for(int i=0;i<=n+m;i++) res[i]=(int)(a[i].real()/tot+0.5);
}
```

