#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <cstdint>
#include <functional>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2208D1: Tree Orientation (Easy Version)
void solve()
{
    int n; cin >> n;
    vector<string> vec(n);
    for (int i = 0; i < n; ++i) {
        cin >> vec[i];
    }

    vector<vector<int>> g1(n), g2(n);
    vector<pair<int, int>> edges;
    for (int i = 0; i < n; ++i) {
        if (vec[i][i] == '0') {
            cout << "No\n";
            return;
        }

        for (int j = 0; j < n; ++j) {
            if (i == j) continue;

            if (vec[i][j] != '1') continue;
            if (vec[j][i] == '1') {
                cout << "No\n";
                return;
            }

            bool has_edge = true;
            for (int k = 0; k < n; ++k) {
                if (k == j || k == i) continue;
                if (vec[i][k] == '1' && vec[k][j] == '1') {
                    has_edge = false;
                }
            }

            if (has_edge) {
                edges.push_back({i, j});
                g1[i].push_back(j);

                g2[i].push_back(j);
                g2[j].push_back(i);
            }
        }
    }

    if (edges.size() != n-1) {
        cout << "No\n";
        return;
    }

    vector<string> new_vec(n, string(n, '0'));
    vector<bool> visited(n);

    bool dfs_ok = true;
    vector<int> vis1(n);
    function<void(int, int)> dfs_1 = [&](int p, int u) {
        vis1[u] = true;
        new_vec[p][u] = '1';

        for (int v: g1[u]) {
            if (vis1[v]) {
                dfs_ok = false;
                cout << "No\n";
                return;
            }
            dfs_1(p, v);
        }
    };

    function<void(int)> dfs_2 = [&](int u) {
        visited[u] = 1;

        for (int v: g2[u]) {
            if (!visited[v]) {
                dfs_2(v);
            }
        }
    };

    for (int i = 0; i < n; ++i) {
        vis1.assign(n, 0);
        dfs_1(i, i);
        if (!dfs_ok) {
            return;
        }
    }

    dfs_2(0);

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            cout << "NO\n";
            return;
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (vec[i][j] != new_vec[i][j]) {
                cout << "No\n";
                return;
            }
        }
    }

    cout << "YES\n";
    for (auto [u, v]: edges) {
        cout << u + 1 << ' ' << v + 1 << '\n';
    }
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
