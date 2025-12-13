#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 1000E: We Need More Bosses
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n+1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> low(n+1, -1), id(n+1);
    int t = 1;
    vector<pair<int, int>> bridges;
    function<void(int, int)> dfs = [&](int u, int p) {
        id[u] = low[u] = t;
        t++;

        for (int v: g[u]) {
            if (v == p) continue;

            if (low[v] == -1) {
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                if (low[v] > id[u]) {
                    bridges.push_back({u, v});
                }
            }
            
            low[u] = min(low[u], low[v]);
        }
    };

    dfs(1, -1);
    map<pair<int, int>, bool> is_bridge;
    for (auto [u, v]: bridges) {
        is_bridge[make_pair(u, v)] = 1;
        is_bridge[make_pair(v, u)] = 1;
    }

    vector<int> p(n+1);
    iota(p.begin() + 1, p.end(), 1);
    function<int(int)> head = [&](int u) {
        if (p[u] == u) return u;
        return p[u] = head(p[u]);
    };

    auto join = [&](int u, int v) {
        int hu = head(u);
        int hv = head(v);
        if (hu == hv) return false;
        p[hv] = p[hu];
        return true;
    };

    vector<bool> vis(n+1);
    vector<vector<int>> g1(n+1);
    function<void(int)> dfs1 = [&](int u) {
        vis[u] = 1;
        for (int v: g[u]) {
            if (vis[v]) continue;

            if (!is_bridge[make_pair(u, v)]) {
                join(u, v);
            } else {
                g1[head(u)].push_back(v);
                g1[v].push_back(head(u));
            }

            dfs1(v);
        }
    };

    dfs1(1);

    const int inf = 1e9;
    vector<int> d(n+1);
    auto build_dist = [&](int u) {
        d.assign(n+1, inf);
        queue<int> q;
        d[u] = 0;
        q.push(u);

        while (q.size() > 0) {
            int v = q.front();
            q.pop();
            for (int vv: g1[v]) {
                if (d[v] + 1 >= d[vv]) continue;
                d[vv] = d[v] + 1;
                q.push(vv);
            }
        }
    };

    build_dist(1);
    int a = -1, b = -1;
    for (int i = 1; i <= n; ++i) {
        if (d[i] == inf) continue;
        if (a == -1 || d[a] < d[i]) {
            a = i;
        }
    }

    build_dist(a);
    for (int i = 1; i <= n; ++i) {
        if (d[i] == inf) continue;
        if (b == -1 || d[b] < d[i]) {
            b = i;
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (d[i] == inf) continue;
        ans = max(ans, d[i]);
    }

    cout << ans << '\n';
}

int T = 1;
int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //cin >> T;
    while(T--)
        solve();

    return 0;
}
