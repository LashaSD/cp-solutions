#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

int timer = 1;
vector<int> tin, tout, p;
vector<vector<int>> g;

struct ST {
    int n;
    vector<int> tree;
    vector<int> lazy;
    ST(int _n): n(_n) 
    {
        tree.resize(4*n + 4, 1);
        lazy.resize(4*n + 4);
    }

    void _push(int node, int tl, int tr)
    {
        if (lazy[node] == 0) return;

        tree[node] = lazy[node];

        if (tl < tr) {
            lazy[2*node] = tree[2*node] = lazy[node];
            lazy[2*node+1] = tree[2*node+1] = lazy[node];
        }

        lazy[node] = 0;
    }

    int _query(int node, int tl, int tr, int l, int r)
    {
        if (l > r) return 2;

        if (l <= tl && tr <= r) {
            return tree[node];
        }

        _push(node, tl, tr);

        int tm = tl + (tr - tl) / 2;

        int vl = _query(2*node, tl, tm, l, min(tm, r));
        int vr = _query(2*node+1, tm+1, tr, max(tm+1, l), r);

        if (vl == 1) return 1;
        if (vr == 1) return 1;
        return 2;
    }

    void _update(int node, int tl, int tr, int l, int r, int v)
    {
        if (l > r) return;

        if (l <= tl && tr <= r) {
            lazy[node] = tree[node] = v;
            _push(node, tl, tr);
            return;
        }

        _push(node, tl, tr);

        int tm = tl + (tr - tl) / 2;
        _update(2*node, tl, tm, l, min(tm, r), v);
        _update(2*node+1, tm+1, tr, max(tm+1, l), r, v);

        if (tree[2*node] == 1)
            tree[node] = tree[2*node];
        else
            tree[node] = tree[2*node+1];
    }

    inline void update(int l, int r, int v)
    {
        _update(1, 0, n-1, l, r, v);
    }

    inline int query(int l, int r)
    {
        return _query(1, 0, n-1, l, r);
    }
};

void dfs(int u)
{
    tin[u] = timer++;

    for (int v: g[u]) {
        if (v == p[u]) continue;
        p[v] = u;
        dfs(v);
    }

    tout[u] = timer++;
}

// 343D: Water Tree
void solve()
{
    int n; cin >> n;
    g.resize(n+1);
    for (int i = 0; i < n-1; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    p.resize(n+1);
    tin.resize(n+1);
    tout.resize(n+1);
    timer = 1;

    p[1] = 0;
    dfs(1);

    ST tree(timer + 1);

    for (int i = 1; i <= n; ++i) {
        tree.update(tin[i], tin[i], 1);
        tree.update(tout[i], tout[i], 1);
    }

    int q; cin >> q;
    for (int qq = 0; qq < q; ++qq) {
        int t, v;
        cin >> t >> v;
        if (t == 1) {
            if (tree.query(tin[v], tout[v]) == 1) {
                if (p[v] > 0) {
                    tree.update(tin[p[v]], tin[p[v]], 1);
                    tree.update(tout[p[v]], tout[p[v]], 1);
                }
            }

            tree.update(tin[v], tout[v], 2);
        } else if (t == 2) {
            tree.update(tin[v], tin[v], 1);
            tree.update(tout[v], tout[v], 1);
        } else if (t == 3) {
            int a = tree.query(tin[v], tout[v]);
            cout << a - 1 << '\n';
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
