ll S[20], cnt, dp[20][180];
// ll dfs(int pos, int last, int limit, int sum)
// {
//     ll ans = 0;
//     if (!pos) return sum;
//     auto &d = dp[pos][last][limit][sum];
//     if (d != -1) return d;//多组样例不可复用记搜
//     for (ll u = 0; u <= (limit ? S[pos] : 9); u++)
//         ans += dfs(pos - 1, u, limit && u == S[pos], sum + u);
//     ans %= mod;
//     d = ans;
//     return ans;
// }
ll dfs(int pos, int limit, int sum)
{
    ll ans = 0;
    if (!pos) return sum;
    auto &d = dp[pos][sum];
    if (!limit && d != -1) return d;// 多组样例可复用记搜
    for (ll u = 0; u <= (limit ? S[pos] : 9); u++)
        ans += dfs(pos - 1, limit && u == S[pos], sum + u);
    ans %= mod;
    if (!limit) d = ans;
    return ans;
}
ll F(ll x)
{
    int cnt = 0;
    // 不可复用记搜时  memset(dp, -1, sizeof(dp));
    while (x) {
        S[++cnt] = x % 10;
        x /= 10;
    }
    return dfs(cnt, true, 0);
}
void solve() {// 求[l,r]所有数位和
    memset(dp, -1, sizeof(dp));
    cin >> l >> r;
    ll ans1 = F(r);
    ll ans2 = F(l - 1);
    cout << ((ans1 - ans2) % mod + mod) % mod << '\n';
}