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
                rk[sa[i]] = rk[sa[i-1]]+(tmp[sa[i-1]]<tmp[sa[i]] || sa[i-1]+k==n || tmp[sa[i-1]+k]<tmp[sa[i]+k]);
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



SA sa(s);
int n=s.size(),m=sa.lc.size(),K = __lg(m);
vector st(K + 1, vector<int>(m));
st[0] = sa.lc;
for (int j = 0; j < K; j++)
    for (int i = 0; i + (2 << j) <= m; i++)
        st[j + 1][i] = min(st[j][i], st[j][i + (1 << j)]);
auto rmq = [&](int l, int r) {
    int k = __lg(r - l);
    return min(st[k][l], st[k][r - (1 << k)]);
};
auto lcp = [&](int i, int j, int x, int y) {//得到s[i..j]与s[x..y]的最长公共前缀子串
    if (i == x || i == j + 1 || x == y + 1)
        return min(j + 1 - i, y + 1 - x);
    int a = sa.rk[i],b = sa.rk[x];
    if (a > b) swap(a, b);
    return min({j + 1 - i, y + 1 - x, rmq(a, b)});
};