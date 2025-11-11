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

// GYM104854J: Judging Gifts
void solve()
{
    int n, m, k, y;
    cin >> n >> m >> k >> y;

    vector<vector<pair<int, int>>> g(n+1);
    for (int i = 0; i < m; ++i) {
        // u can be exchanged with v, using w coins
        int u, v, w;
        cin >> u >> v >> w;
        g[v].push_back({w, u});
    }

    vector<bool> visited(n+1), processing(n+1);
    function<bool(int)> cycleDfs = [&](int u) {
        visited[u] = 1;
        processing[u] = 1;
        for (auto [w, v]: g[u]) {
            if (visited[v] && processing[v]) {
                return true;
            }

            if (!visited[v]) {
                if (cycleDfs(v)) return true;
            }
        }

        processing[u] = 0;
        return false;
    };

    bool has_cycle = cycleDfs(y);
    if (has_cycle) {
        cout << "YES\n";
        return;
    }

    vector<int> d(n+1, LLONG_MIN);
    set<pair<int, int>> q;
    q.insert({0, y});
    d[y] = 0;
    while (!q.empty()) {
        auto [_u, u] = *q.begin();
        q.erase(q.begin());
        if (d[u] > (-_u)) continue;

        for (auto [uv, v]: g[u]) {
            if (d[u] + uv > d[v]) {
                d[v] = d[u] + uv;
                // cerr << "DBG: " << u << ' ' << v << ' ' << d[v] << '\n';
                q.insert({-d[v], v});
            }
        }
    }

    int k1 = 0;
    for (int i = 1; i <= n; ++i) {
        k1 = max(k1, d[i]);
    }

    cerr << "MX: " << k1 << '\n';

    cout << (k1 >= k ? "YES\n" : "NO\n");
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
