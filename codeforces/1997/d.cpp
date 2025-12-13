#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll

// 1997D: Maximize the Root
void solve()
{
    int n; cin >> n;
    vector<int> a(n+1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    vector<vector<int>> g(n+1);
    for (int u = 2; u <= n; ++u) {
        int v; cin >> v;
        g[v].push_back(u);
    }

    vector<int> dp(n+1, LLONG_MAX);
    function<void(int, int)> dfs = [&](int u, int p) {
        int mn = LLONG_MAX;
        bool f = false;
        for (int v: g[u]) {
            if (v == p) continue;
            f = 1;
            dfs(v, u);
            mn = min(mn, dp[v]);
        }

        if (!f) {
            dp[u] = a[u];
            return;
        }

        if (a[u] > mn) {
            dp[u] = mn;
        } else {
            dp[u] = (a[u] + mn) / 2;
        }
    };

    dfs(1, -1);

    int ans = INT_MAX;
    for (int v: g[1])
        ans = min(ans, dp[v]);

    ans += a[1];
    cout << ans << '\n';
}

int T = 1;
int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while(T--)
        solve();

    return 0;
}
