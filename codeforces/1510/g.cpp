#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define xx first
#define yy second

// 1510G: Guide
void solve()
{
    int n, k;
    cin >> n >> k;
    vector<vector<int>> g(n+1);
    for (int i = 1; i <= n-1; ++i) {
        int u = i+1;
        int v; cin >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> d(n+1, -1);
    function<int(int, int)> dfs1 = [&](int u, int p) {
        int mx = 0;
        for (int v: g[u]) {
            if (v == p) continue;
            int x = dfs1(v, u);
            if (x > mx) {
                d[u] = v;
                mx = x;
            }
        }

        return 1 + mx;
    };

    vector<int> ans;

    function<int(int, int, int)> dfs2 = [&](int u, int p, int leftover) {
        if (leftover == 0) return 0;
        ans.push_back(u);
        leftover--;

        for (int v: g[u]) {
            if (v == p) continue;
            int old = leftover;
            leftover = dfs2(v, u, leftover);
            if (old != leftover) {
                ans.push_back(u);
            }
        }

        return leftover;
    };

    int depth = dfs1(1, -1);
    if (depth >= k) {
        int u = 1;
        while ((int) ans.size() < k && u != -1) {
            ans.push_back(u);
            u = d[u];
        }

        cout << ans.size() - 1 << '\n';
        for (int x: ans) {
            cout << x << ' ';
        }
        cout << '\n';
        return;
    }

    int pu = -1, u = 1;
    int leftover = max(0, k - depth);
    while (u != -1) {
        ans.push_back(u);
        int nu = d[u];
        for (int v: g[u]) {
            if (v == pu || v == nu) continue;
            int old = leftover;
            leftover = dfs2(v, u, leftover);
            if (old != leftover) {
                ans.push_back(u);
            }
        }

        pu = u;
        u = nu;
        if (nu == -1) break;
    }

    cout << ans.size() - 1 << '\n';
    for (int x: ans) {
        cout << x << ' ';
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
