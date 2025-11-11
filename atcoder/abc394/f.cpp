#include <iostream>
#include <cassert>
#include <climits>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <functional>

using namespace std;
using ll = long long;

#define int ll

const int maxN = 2e5;
vector<vector<int>> dp(maxN + 1, vector<int>(4));

// ABC394F: Alkane 
void solve()
{
    int n; cin >> n;
    vector<vector<int>> g(n+1);
    for (int i = 0; i < n-1; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<bool> ok(n+1);
    function<void(int, int)> dfs = [&](int u, int p) {
        vector<int> vals(g[u].size());

        for (int v: g[u]) {
            if (v == p) continue;
            dfs(v, u);

            int cnt = g[v].size();
            if (dp[v][2] > 0) {
                vals.push_back(dp[v][0] + dp[v][1] + dp[v][2] + 1);
                ok[u] = 1;
            } else {
                vals.push_back(1);
            }
        }

        sort(vals.begin(), vals.end(), greater<int>());
        for (int i = 0; i < min(4ll, (int) vals.size()); ++i) {
            dp[u][i] = vals[i];
        }
    };

    dfs(1, -1);

    int ans = -1;
    for (int u = 1; u <= n; ++u) {
        //cerr << "U: " << u << ": ";
        //for (int i = 0; i < 4; ++i) {
        //    cerr << dp[u][i] << ' ';
        //}
        //cerr << '\n';

        if (dp[u][3] > 0) {
            //cerr << "OK: " << u << '\n';
            ans = max(ans, dp[u][0] + dp[u][1] + dp[u][2] + dp[u][3] + 1);
        } else if (ok[u]) {
            //cerr << "OK: " << u << '\n';
            ans = max(ans, dp[u][0] + 1);
        }
    }

    cout << ans << '\n';
}

int T = 1;
int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // cin >> T;
    while(T--)
        solve();

    return 0;
}
