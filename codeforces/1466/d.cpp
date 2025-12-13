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

// 1466D: 13th Labour of Heracles
void solve()
{
    int n; cin >> n;
    vector<int> w(n+1);
    for (int i = 1; i <= n; ++i) {
        cin >> w[i];
    }

    vector<set<int>> g(n+1);
    for (int i = 0; i < n-1; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].insert(v);
        g[v].insert(u);
    }

    set<pair<int, int>> st;
    for (int u = 1; u <= n; ++u) {
        if (g[u].size() > 1)
            st.insert({-w[u], u});
    }

    int ans = 0;
    vector<int> cnt(n+1, 1), max_cnt(n+1);
    for (int i = 1; i <= n; ++i) {
        ans += w[i];
        max_cnt[i] = g[i].size();
    }

    cout << ans << ' ';
    for (int k = 1; k < n-1; ++k) {
        if (st.size() == 0) {
            cout << ans << ' ';
            continue;
        }

        auto it = st.begin();
        int u = it->second;
        int v = *g[u].begin();

        g[u].erase(v);
        g[v].erase(u);

        ans += w[u];
        cnt[u]++;

        if (cnt[u] == max_cnt[u]) {
            st.erase(it);
        }

        cout << ans << ' ';
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
