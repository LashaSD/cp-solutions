#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 609E: Minimum spanning tree for each edge
void solve()
{
    int n, m;
    cin >> n >> m;
    using P = pair<int, pair<int, int>>;
    vector<P> vec(m);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        vec[i].xx = w;
        vec[i].yy.xx = u;
        vec[i].yy.yy = v;
    }

    vector<int> p(n+1);
    for (int i = 1; i <= n; ++i) {
        p[i] = i;
    }

    auto head = [&](auto& self, int u)
    {
        if (p[u] == u) return u;
        return p[u] = self(self, p[u]);
    };

    auto join = [&](int u, int v) 
    {
        int hu = head(head, u);
        int hv = head(head, v);
        if (hu == hv) return false;

        p[hu] = hv;
        return true;
    };

    vector<int> a(m);
    iota(a.begin(), a.end(), 0);
    sort(a.begin(), a.end(), [&](int a, int b) {
                return vec[a].xx < vec[b].xx;
            });

    vector<bool> in_mst(m+1);
    vector<vector<pair<int, int>>> g(n+1);
    int mst = 0;
    for (int i = 0; i < m; ++i) {
        auto [w, pp] = vec[a[i]];
        auto [u, v] = pp;
        if (join(u, v)) {
            in_mst[a[i]] = 1;
            mst += w;
            g[u].push_back({w, v});
            g[v].push_back({w, u});
        }
    }

    int B = 63 - __builtin_clzll(n);
    vector<vector<int>> up(B+1, vector<int>(n+1));
    vector<vector<int>> upw(B+1, vector<int>(n+1));
    vector<int> tin(n+1), tout(n+1);
    int timer = 0;
    function<void(int, int, int)> dfs = [&](int u, int _w, int p) 
    {
        tin[u] = timer++;
        up[0][u] = p;
        upw[0][u] = _w;
        for (int i = 1; i <= B; ++i) {
            up[i][u] = up[i-1][up[i-1][u]];
            upw[i][u] = max(upw[i-1][u], upw[i-1][up[i-1][u]]);
        }

        for (auto [w, v]: g[u]) {
            if (v == p) continue;
            dfs(v, w, u);
        }

        tout[u] = timer++;
    };

    auto is_anc = [&](int u, int v)
    {
        return tin[u] <= tin[v] && tout[v] <= tout[u];
    };

    auto lca = [&](int u, int v)
    {
        int l = 0, r = 0;
        int hu = u, hv = v;
        if (!is_anc(u, v)) {
            for (int i = B; i >= 0; --i) {
                if (!is_anc(up[i][hu], v)) {
                    l = max(l, upw[i][hu]);
                    hu = up[i][hu];
                }
            }
            l = max(l, upw[0][hu]);
        }
        
        if (!is_anc(v, u)) {
            for (int i = B; i >= 0; --i) {
                if (!is_anc(up[i][hv], u)) {
                    r = max(r, upw[i][hv]);
                    hv = up[i][hv];
                }
            }
            r = max(r, upw[0][hv]);
        }

        return max(l, r);
    };

    dfs(1, 0, 1);

    for (int i = 0; i < m; ++i) {
        auto [w, pp] = vec[i];
        auto [u, v] = pp;
        if (in_mst[i]) {
            cout << mst << '\n';
        } else {
            cout << mst - lca(u, v) + w << '\n';
        }
    }
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
