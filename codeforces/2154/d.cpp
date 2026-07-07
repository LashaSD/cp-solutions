#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <cstdint>
#include <set>
#include <cstdio>
#include <algorithm>
#include <functional>
#include <map>

#define assert(v) do { if (!(v)) { *(int*)0 = 0; } } while (0)

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2154D: Catshock
void solve()
{
    int n; cin >> n;
    vector<vector<int>> g(n+1);
    vector<int> deg(n+1);
    for (int i = 0; i < n-1; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }

    vector<int> d(n+1);
    function<void(int, int)> dfs = [&](int u, int p) {
        for (int v: g[u]) {
            if (v == p) continue;
            d[v] = d[u] + 1;
            dfs(v, u);
        }
    };

    dfs(1, 0);

    // a = even dist leaves
    // b = odd dist leaves
    vector<int> a, b;
    for (int i = 1; i < n; ++i) {
        if (deg[i] == 1) {
            if (d[i] % 2 == 0) {
                a.push_back(i);
            } else {
                b.push_back(i);
            }
        }
    }

    vector<int> p(n+1);
    vector<pair<int, int>> ops;

    int move_cnt = 0;
    while (a.size() > 0 || b.size() > 0) {
        int u = -1;
        if (move_cnt % 2 == 0) {
            if (b.size() == 0) {
                ops.push_back({1, 0});
                move_cnt++;
                continue;
            } else {
                u = b.back();
                b.pop_back();
            }
        } else {
            if (a.size() == 0) {
                ops.push_back({1, 0});
                move_cnt++;
                continue;
            } else {
                u = a.back();
                a.pop_back();
            }
        }

        ops.push_back({2, u});
        for (int v: g[u]) {
            if (v == p[u]) continue;
            if (v == n) continue;

            deg[v]--;
            p[v] = u;

            if (deg[v] == 1) {
                if (d[v] % 2 == 0) {
                    a.push_back(v);
                } else {
                    b.push_back(v);
                }
            }
        }

        ops.push_back({1, 0});
        move_cnt++;
    }

    cout << ops.size() << '\n';
    for (int i = 0; i < (int)ops.size(); ++i) {
        auto [o, w] = ops[i];
        if (o == 2) {
            cout << 2 << ' ' << w << '\n';
        } else {
            cout << 1 << '\n';
        }
    }
}

int T = 1;
int32_t main(void)
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    cin >> T;
    while(T--)
        solve();

    return 0;
}
