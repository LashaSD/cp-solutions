#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

const int MOD = 998244353;

// 2070D: Tree Jumps
void solve()
{
    int n; cin >> n;
    vector<vector<int>> g(n+1);
    vector<int> p(n+1);

    p[1] = 1;
    for (int i = 2; i <= n; ++i) {
        int v; cin >> v;
        p[i] = v;
        g[v].push_back(i);
    }

    vector<int> dp(n+1), t(n+1);

    queue<pair<int, int>> q;
    q.push({1, 0});
    dp[1] = 1;
    while (q.size() > 0) {
        auto [u, d] = q.front();
        q.pop();

        if (d > 0) {
            if (p[u] == 1) {
                dp[u] = 1;
            } else {
                dp[u] = (MOD + t[d-1] - dp[p[u]]) % MOD;
            }
        }

        t[d] = (t[d] + dp[u]) % MOD;

        for (int v: g[u]) {
            q.push({v, d + 1});
        }
    }

    ll ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans = (ans + dp[i]) % MOD;
    }

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
