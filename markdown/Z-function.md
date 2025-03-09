### Z-function

第一个zFunction得到s串每个**后缀与原s串**的**最长公共前缀(LCP)**
**(ababa   5 0 3 0 1)**
第二个zFunction先对模式串p进行第一个z函数预处理
匹配文本串s,得到s串的每个后缀与p串的**最长公共前缀(LCP)**

```c++
vector<int> zFunction(string &s)
{
    int n=s.size();
    vector<int> z(n);
    z[0]=n;
    for (int i=1,j=1;i<n;i++)
    {
        z[i]=max(0,min(j+z[j]-i,z[i-j]));
        while(i+z[i]<n && s[z[i]]==s[i+z[i]])
            z[i]++;
        if(i+z[i]>j+z[j])
            j=i;
    }
    return z;
}
vector<int> zFunction(string &s,string &p,vector<int>& z)
{
    int n=s.size(),m=p.size();
    vector<int> Z(n);
    Z[0]=0;
    for(int i=0,j=0;i<n;i++)
    {
        Z[i]=max(0,min(j+Z[j]-i,z[i-j]));
        while(i+Z[i]<n && Z[i]<m && p[Z[i]]==s[i+Z[i]])
            Z[i]++;
        if(i+Z[i]>j+Z[j])
            j=i;
    }
    return Z;
}
```

