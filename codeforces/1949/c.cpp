#include <iostream>
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

// 1949C: Annual Ants' Gathering
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

    set<pair<int, int>> q;
    vector<int> d(n+1, 1), e(n+1, 1);
    vector<bool> vis(n+1);
    for (int u = 1; u <= n; ++u) {
        e[u] = g[u].size();
        if (e[u] == 1) {
            q.insert({1, u});
        }
    }

    while (!q.empty()) {
        auto [_, u] = *q.begin();
        q.erase(q.begin());

        vis[u] = 1;
        for (auto v: g[u]) {
            if (vis[v]) continue;

            if (d[v] >= d[u]) {
                d[v] += d[u];
                d[u] = 0;
                e[u]--, e[v]--;
                if (e[v] == 1)
                    q.insert({d[v] + d[u], v});
            }

            break;
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (d[i] == n) {
            cout << "YES\n";
            return;
        }
    }

    cout << "NO\n";
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
