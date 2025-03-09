### SuffixArray

rk[i]表示从第i位开始,长度为K的字串(长度不足K串尾补0)在所有长度为K子串中的**排名**
sa[i]表示长度为K的子串中字典序第i小的字串在原串中的**开始位置**
lc[i]表示排序后的后缀子串,相邻两字串的**最长公共前缀子串(LCP)**
rk排名从0开始,sa开始位置从0开始
sa以及lc下标对应排完序的后缀子串编号,rk下标对应的原字符串下标
banana(排完序所有后缀:a  ana  anana  banana  na  nana)
基于基数排序的实现方式,时间复杂度$O(nlogn)$
本质不同子串$(O(n))$=$\frac{n(n+1)}{2}-\sum lc[i]$(总子串-重复子串)**[不能预处理区间查询]**
本质不同子序列$(O(n))$:dp[i]=2dp[i-1]+1或dp[i]=2dp[i-1]-dp[lst-1]

```c++
struct SA {
    int n;
    vector<int> sa, rk, lc;
    SA(string s) {
        n = s.size();
        sa.resize(n);
        lc.resize(n - 1);
        rk.resize(n);
        iota(sa.begin(), sa.end(), 0);
        sort(sa.begin(), sa.end(),[&](int a,int b){return s[a]<s[b];});
        rk[sa[0]] = 0;
        for (int i = 1; i < n; i++) {
            rk[sa[i]] = rk[sa[i - 1]] + (s[sa[i]] != s[sa[i - 1]]);
        }
        int k = 1;
        vector<int> tmp, cnt(n);
        tmp.reserve(n);
        while (rk[sa[n - 1]] < n - 1) {
            tmp.clear();
            for (int i = 0; i < k; i++)
                tmp.push_back(n - k + i);
            for (auto i : sa)
                if (i >= k)
                    tmp.push_back(i - k);
            fill(cnt.begin(), cnt.end(), 0);
            for (int i = 0; i < n; i++)
                cnt[rk[i]]++;
            for (int i = 1; i < n; i++)
                cnt[i] += cnt[i - 1];
            for (int i = n - 1; i >= 0; i--)
                sa[--cnt[rk[tmp[i]]]] = tmp[i];
            swap(rk, tmp);
            rk[sa[0]] = 0;
            for (int i = 1; i < n; i++) {
                rk[sa[i]] = rk[sa[i-1]]+(tmp[sa[i-1]]<tmp[sa[i]] 
                                   || sa[i-1]+k==n || tmp[sa[i-1]+k]<tmp[sa[i]+k]);
            }
            k *= 2;
        }
        for (int i = 0, j = 0; i < n; i++) {
            if (rk[i] == 0) j = 0;
			else {
                for (j-=j>0;i+j<n && sa[rk[i]-1]+j<n && s[i+j]==s[sa[rk[i]-1]+j];)
                    j++;
                lc[rk[i] - 1] = j;
            }
        }
    }
};
```

---

$LCP(s_1=s[l_1..r_1],s_2=s[l_2..r_2])=\min(|s_1|,|s_2|,lcp(sa[l_1],sa[l_2]))$
$lcp(sa[l_1],sa[l_2])=\min_{l_1\lt k\le l_2}(lc[k])$
**特判字符串长度为1**$(因为当len=1时,sa.lc为空)$
lcp函数得到$s[i..j]与s[x..y]$的最长公共前缀子串

```c++
SA sa(s);
int n=s.size(),m=sa.lc.size();
int K = __lg(m);
vector st(K + 1, vector<int>(m));
st[0] = sa.lc;
for (int j = 0; j < K; j++) {
    for (int i = 0; i + (2 << j) <= m; i++) {
        st[j + 1][i] = min(st[j][i], st[j][i + (1 << j)]);
    }
}

auto rmq = [&](int l, int r) {
    int k = __lg(r - l);
    return min(st[k][l], st[k][r - (1 << k)]);
};

auto lcp = [&](int i, int j, int x, int y) {//最长公共前缀
    if (i == x || i == j + 1 || x == y + 1) {
        return min(j + 1 - i, y + 1 - x);
    }
    int a = sa.rk[i];
    int b = sa.rk[x];
    if (a > b) {
        swap(a, b);
    }
    return min({j + 1 - i, y + 1 - x, rmq(a, b)});
};
```

在求两字符串**最长公共子串**时,需要通过**特殊字符**连接两个字符串(例:**k  sks**不通过特殊字符分割求得最长公共子串为2)**[多串同理,滑动窗口保证当前x个后缀的前缀来自n个不同字符串]**
```c++
s=a+"|"+b;
SA sa(s);
int ans=0;
for(int i=1;i<sa.sa.size();i++)
{
    int x=sa.sa[i-1],y=sa.sa[i];
    if(x>y) swap(x,y);
    if(0<=x && x<a.size() && a.size()<y && y<=a.size()+b.size())
        ans=max(ans,sa.lc[i-1]); 
}
cout<<ans<<"\n";
```

