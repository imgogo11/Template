### josephus

```c++
int f(int n,int m,int k)//第m轮结果
{
    if(m==1) return (k-1)%n;
    return (f(n-1,m-1,k)+k)%n;
}
```

