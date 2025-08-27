#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

// 1946C: Tree Cutting
void solve()
{
    int n, k;
    cin >> n >> k;
    vector<vector<int>> g(n+1);
    for (int i = 0; i < n-1; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    function<pair<int, int>(int, int, int)> dfs = [&](int u, int parent, int x) {
        int nodes = 1;
        int cuts = 0;

        for (int v: g[u]) {
            if (v == parent) continue;
            pair<int, int> res = dfs(v, u, x);
            nodes += res.first;
            cuts += res.second;
        }

        if (nodes >= x) nodes = 0, cuts++;

        return (pair<int, int>){ nodes, cuts };
    };

    int l = 0, r = n;
    int ans = -1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        auto ret = dfs(1, -1, mid);
        bool ok = (ret.first >= mid && ret.second == k) || ret.second > k;
        if (ok) {
            l = mid + 1;
            ans = mid;
        } else {
            r = mid - 1;
        }
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
