#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <cstdint>
#include <set>
#include <algorithm>
#include <assert.h>
#include <functional>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

struct Data {
    int depth = 0;
    int cost_sum = 0; // a1 + a2 + a3 ...
    int base_cost = 0; // a1*depth_1 + a2*depth_2 + a3*depth_3 ...
    int max_cost = LLONG_MIN; // ans
};

vector<int> a;
vector<vector<int>> g;
vector<Data> dp;

void dfs(int u, int p)
{
    for (int v: g[u]) {
        if (v == p) continue;
        dfs(v, u);
    }

    int child_count = g[u].size() - (u != 1);
    if (child_count == 0) {
        dp[u].depth = 1;
        dp[u].base_cost = 0;
        dp[u].cost_sum = a[u];
        dp[u].max_cost = 0;
        return;
    }

    int max_depths[2] = {-1, -1};

    dp[u].base_cost = 0;
    dp[u].cost_sum = a[u];
    for (int v: g[u]) {
        if (v == p) continue;

        dp[u].depth = max(dp[u].depth, dp[v].depth + 1);
        dp[u].base_cost += dp[v].base_cost + dp[v].cost_sum;
        dp[u].cost_sum += dp[v].cost_sum;

        if (max_depths[1] == -1 || dp[v].depth > dp[max_depths[1]].depth) {
            max_depths[0] = max_depths[1];
            max_depths[1] = v;
        } else if (max_depths[0] == -1 || dp[v].depth > dp[max_depths[0]].depth) {
            max_depths[0] = v;
        }
    }

    for (int v: g[u]) {
        if (v == p) continue;

        ll v_max_cost = dp[v].max_cost + dp[v].cost_sum;

        if (child_count >= 2) {
            int mx_depth = max_depths[1];
            if (mx_depth == v) mx_depth = max_depths[0];
            mx_depth = dp[mx_depth].depth + 1;

            v_max_cost = max(v_max_cost, dp[v].base_cost + dp[v].cost_sum * mx_depth);
        }

        ll v_base_contrib = dp[v].base_cost + dp[v].cost_sum;
        dp[u].max_cost = max(dp[u].max_cost, dp[u].base_cost - v_base_contrib + v_max_cost);
    }
};

// 2192D: Cost of Tree
void solve()
{
    int n; cin >> n;
    a.resize(n+1);
    g.resize(n+1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        g[i].clear();
    }

    for (int i = 0; i < n-1; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dp.resize(n+1);
    for (int i = 1; i <= n; ++i) {
        dp[i] = Data{};
    }

    dfs(1, 0);

    for (int i = 1; i <= n; ++i) {
        cout << dp[i].max_cost << ' ';
    }
    cout << '\n';
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
