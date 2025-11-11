#include <iostream>
#include <cassert>
#include <climits>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <map>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 1266D: Decreasing Debts
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> in(n+1), out(n+1);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        out[u] += w;
        in[v] += w;
    }

    vector<pair<int, int>> neg, pos;
    for (int i = 1; i <= n; ++i) {
        int d = in[i] - out[i];
        if (d > 0) pos.push_back(make_pair(i, d));
        if (d < 0) neg.push_back(make_pair(i, -d));
    }

    vector<pair<pair<int, int>, int>> edges;
    int i = 0, j = 0;
    int m1 = pos.size(), m2 = neg.size();
    while (i < m1 && j < m2) {
        int mn = min(pos[i].yy, neg[j].yy);

        pos[i].yy -= mn;
        neg[j].yy -= mn;
        edges.push_back({{neg[j].xx, pos[i].xx}, mn});

        if (pos[i].yy == 0) i++;
        if (neg[j].yy == 0) j++;
    }

    cout << edges.size() << '\n';
    for (int i = 0; i < (int) edges.size(); ++i) {
        cout << edges[i].xx.xx << ' ' << edges[i].xx.yy << ' ' << edges[i].yy << '\n';
    }
}

int T = 1;
int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // cin >> T;
    while(T--)
        solve();

    return 0;
}
