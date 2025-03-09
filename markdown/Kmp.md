### Kmp

对模式串b预处理PMT(Partial Match Table)
在文本串a中查找模式串b
pmt代表模式串每个前缀的最大前缀和后缀匹配个数(==**ABC**==D==**ABC**==------3)

```c++
int pmt[N],pos[N],cnt;
void get_pmt(string& s) {
    memset(pmt,0,sizeof(int)*(s.size()+5));
    for(int i=1,j=0;i<s.size();i++) {
        while(j && s[i]!=s[j]) j=pmt[j-1];
        if(s[i]==s[j]) j++;
        pmt[i]=j;
    }
}
bool kmp(string& s,string& p) {
    cnt=0;
    for(int i=0,j=0;i<s.size();i++) {
        while(j && s[i]!=p[j]) j=pmt[j-1];
        if(s[i]==p[j]) j++;
        if(j==p.size()) {
            pos[++cnt]=i-j+2;
            j=pmt[j-1];
        }
    }
    return cnt>0;
}
```

