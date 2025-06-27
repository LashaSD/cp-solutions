#include <climits>
#include <cstdio>
#include <algorithm>
#include <cstdint>
#include <queue>
#include <vector>
#include <queue>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

// C. Dijkstra?
void solve()
{
    ll n, m;
    scanf("%lld %lld", &n, &m);
    // node -> { first: node, second: weight }
    vector<vector<pair<ll, ll>>> g(n + 1);
    for (int i = 0; i < m; ++i) {
        ll u, v, w;
        scanf("%lld %lld %lld", &u, &v, &w);
        g[u].push_back({ v, w });
        g[v].push_back({ u, w });
    }

    vector<ll> p(n + 1, -1);
    vector<ll> d(n + 1, LLONG_MAX);
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> q;
    q.push({0, 1});
    d[1] = 0;
    while (not q.empty()) {
        auto info = q.top();
        q.pop();
        ll u = info.second;
        ll dist = info.first;
        for (auto& e : g[u]) {
            ll v = e.first;
            ll w = e.second;
            ll new_dist = dist + w;
            if (new_dist < d[v]) {
                q.push({ new_dist, v });
                p[v] = u;
                d[v] = new_dist;
            }
        }
    }

    if (p[n] == -1) {
        printf("-1\n");
    } else {
        vector<ll> path;
        ll current = n;
        while (p[current] != -1) {
            path.push_back(current);
            current = p[current];
        }
        path.push_back(1);
        for (auto it = path.rbegin(); it != path.rend(); ++it) {
            printf("%lld ", *it);
        }
        printf("\n");
    }
}

int T = 1;
int32_t main(void)
{
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    // scanf("%d", &T);
    while(T--)
        solve();
    return 0;
}
