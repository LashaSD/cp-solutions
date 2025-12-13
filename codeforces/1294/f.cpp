#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

int n;
vector<vector<int>> g;

int ddfs(int u, int p)
{
    int dist = 0;
    for (int v: g[u]) {
        if (v == p) continue;
        dist += ddfs(v, p);
    }

    return 1 + dist;
}

vector<int> d, p;

void dist_dfs(int u)
{
    for (int v: g[u]) {
        if (v == p[u]) continue;

        d[v] = d[u] + 1;
        p[v] = u;
        dist_dfs(v);
    }
}

void dist(int u)
{
    d.assign(n+1, 0);
    p.assign(n+1, 0);
    p[u] = 0;
    dist_dfs(u);
}

// 1294F: Three Paths on a Tree
void solve()
{
    cin >> n;
    g.resize(n+1);
    d.resize(n+1);
    p.resize(n+1);
    for (int i = 0; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int a = 1, b = 1;
    dist(1);
    for (int i = 1; i <= n; ++i) {
        if (d[i] > d[a]) {
            a = i;
        }
    }

    dist(a);
    for (int i = 1; i <= n; ++i) {
        if (d[i] > d[b]) {
            b = i;
        }
    }

    vector<int> da = d;
    dist(b);
    vector<int> db = d;

    vector<int> nodes;
    vector<bool> mark(n+1);
    int v = a;
    while (v > 0) {
        mark[v] = 1;
        nodes.push_back(v);
        v = p[v];
    }

    int ans = da[b];
    int c = 0, mx = 0;
    for (int i = 1; i <= n; ++i) {
        if (!mark[i]) {
            int len = (da[i] + db[i] - ans) / 2;
            if (len > mx) {
                c = i;
                mx = len;
            }
        }
    }

    if (c == 0) {
        c++;
        while (c == a || c == b) c++;
    }
    
    cout << ans + mx << '\n';
    cout << a << ' ' << b << ' ' << c << '\n';
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
