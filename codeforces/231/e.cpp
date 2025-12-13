#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define xx first
#define yy second

const int mod = 1e9 + 7;
const int maxN = 1e5;

int n, m;
vector<int> g[maxN + 1], t[maxN + 1];

int p[maxN + 1], s[maxN + 1];
int low[maxN + 1], tin[maxN + 1], tout[maxN + 1];
bool vis[maxN + 1];

map<pair<int, int>, bool> is_bridge;
int timer = 1;

int up[21][maxN];
int cy[21][maxN];

int head(int u) 
{
    if (p[u] == u) return u;
    return p[u] = head(p[u]);
}

bool join(int u, int v)
{
    int hu = head(u);
    int hv = head(v);
    if (hu == hv) return false;
    p[hv] = hu;
    s[hu] += s[hv];
    return true;
}

void build_t()
{
    for (int i = 1; i <= n; ++i) {
        p[i] = i;
        s[i] = 1;
        low[i] = -1;
    }

    timer = 1;

    function<void(int, int)> dfs = [&](int u, int p) {
        low[u] = tin[u] = timer++;

        for (int v: g[u]) {
            if (v == p) continue;

            if (low[v] == -1) {
                dfs(v, u);
                if (low[v] > tin[u]) {
                    is_bridge[make_pair(u, v)] = 1;
                    is_bridge[make_pair(v, u)] = 1;
                }
            }

            low[u] = min(low[u], low[v]);
        }

        tout[u] = timer++;
    };

    function<void(int)> t_dfs = [&](int u) {
        vis[u] = 1;
        for (int v: g[u]) {
            if (vis[v]) continue;

            if (is_bridge[make_pair(u, v)]) {
                t[head(u)].push_back(v);
                t[v].push_back(head(u));
            } else {
                join(u, v);
            }

            t_dfs(v);
        }
    };

    dfs(1, -1);
    t_dfs(1);
}

static inline bool is_anc(int u, int v)
{
    return tin[u] <= tin[v] && tout[v] <= tout[u];
}

static inline bool is_cy(int u)
{
    return s[head(u)] > 1;
}

void build_lca()
{
    timer = 1;
    int B = 31 - __builtin_clz(n);
    function<void(int, int)> dfs = [&](int u, int p) {
        tin[u] = timer++;

        up[0][u] = p;
        cy[0][u] = is_cy(u);

        for (int j = 1; j <= B; ++j) {
            up[j][u] = up[j-1][up[j-1][u]];

            if (up[j-1][u] != up[j-1][up[j-1][u]]) {
                cy[j][u] = cy[j-1][u] + cy[j-1][up[j-1][u]];
            } else {
                cy[j][u] = cy[j-1][u];
            }
        }

        for (int v: t[u]) {
            if (v == p) continue;
            dfs(v, u);
        }

        tout[u] = timer++;
    };

    dfs(1, 1);
}


int path_len(int u, int v)
{
    if (u == v) {
        return cy[0][u];
    }

    int B = 31 - __builtin_clz(n);

    int lca = 0;
    ll pu = 0, pv = 0;
    int tu = u, tv = v;
    if (!is_anc(u, v)) {
        for (int j = B; j >= 0; --j) {
            if (!is_anc(up[j][tu], v)) {
                pu += cy[j][tu];
                tu = up[j][tu];
            }
        }

        lca = up[0][tu];
        pu += cy[0][tu];
    }

    if (!is_anc(v, u)) {
        for (int j = B; j >= 0; --j) {
            if (!is_anc(up[j][tv], u)) {
                pv += cy[j][tv];
                tv = up[j][tv];
            }
        }

        lca = up[0][tv];
        pv += cy[0][tv];
    }

    return pu + pv + cy[0][lca];
}

// 231E: Cactus
void solve()
{
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<ll> pow2(n+1);
    pow2[0] = 1;
    for (int i = 1; i <= n; ++i) {
        pow2[i] = (pow2[i-1] * 2) % mod;
    }

    build_t();
    build_lca();

    int k; cin >> k;
    for (int ki = 0; ki < k; ++ki) {
        int u, v;
        cin >> u >> v;
        int hu = head(u), hv = head(v);
        int cnt = path_len(hu, hv);
        cout << pow2[cnt] << '\n';
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
