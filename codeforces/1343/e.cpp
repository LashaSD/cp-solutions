#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

const int inf = LLONG_MAX >> 3;
int n, m, a, b, c;
vector<vector<int>> g;
vector<int> d;

void dist(int u)
{
    d.assign(n+1, inf);
    queue<int> q;
    q.push(u);
    d[u] = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int vv: g[v]) {
            if (d[v] + 1 < d[vv]) {
                d[vv] = d[v] + 1;
                q.push(vv);
            }
        }
    }
}

// 1343E: Weights Distributing
void solve()
{
    cin >> n >> m >> a >> b >> c;

    vector<int> prices(m+1);
    for (int i = 1; i <= m; ++i) {
        cin >> prices[i];
    }

    sort(prices.begin() + 1, prices.end());
    vector<int> pref(m+1);
    for (int i = 1; i <= m; ++i) {
        pref[i] = pref[i-1] + prices[i];
    }

    g.assign(n+1, vector<int>());
    d.assign(n+1, 0);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dist(a);
    vector<int> da = d;

    dist(b);
    vector<int> db = d;

    dist(c);
    vector<int> dc = d;

    int ans = inf;
    for (int i = 1; i <= n; ++i) {
        int b_cost = pref[db[i]];
        int rest = db[i] + da[i] + dc[i];
        if (rest > m) continue;
        int cost = pref[db[i] + da[i] + dc[i]] + b_cost;
        //cerr << "DBG: " << i << ' ' << db[i] + da[i] + dc[i] << ' ' << cost << '\n';
        ans = min(ans, cost);
    }

    cout << ans << '\n';
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
