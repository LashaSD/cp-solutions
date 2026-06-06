#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <cstdint>
#include <set>
#include <algorithm>
#include <assert.h>
#include <functional>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

void ask(int k, vector<int> &store)
{
    (cout << "? " << k << '\n').flush();
    int q; cin >> q;
    store.clear();
    for (int i = 0; i < q; ++i) {
        int u; cin >> u;
        store.push_back(u);
    }
}

// 2196C2: Interactive Graph (Hard Version)
void solve()
{
    int n; cin >> n;

    vector<vector<int>> adj(n+1, vector<int>(n+1));
    int k = 2;
    vector<pair<int, int>> st{{1,1}};
    vector<int> path, memo(n+1);
    while (true) {
        ask(k, path);

        int slen = st.size();
        int plen = path.size();
        if (plen == 0) break;
        for (int i = 1; i < plen; ++i) {
            adj[path[i-1]][path[i]] = 1;
        }

        int last = path.back();
        int t = plen >= 2 ? path[plen - 2] : -1;
        while (st.size() > 0 && st.back().xx != t) {
            auto [u, w] = st.back();
            memo[u] = w;
            st.pop_back();
            if (st.size() > 0) {
                st.back().yy += w;
            }
        }

        if (memo[last] != 0) {
            k += memo[last];
            if (st.size() > 0) {
                st.back().yy += memo[last];
            }
        } else {
            k++;
            st.push_back({last, 1});
        }
    }

    vector<pair<int, int>> edges;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (adj[i][j]) {
                edges.push_back({i, j});
            }
        }
    }

    cout << "! " << edges.size() << '\n';
    for (auto [u, v]: edges) {
        cout << u << ' ' << v << '\n';
    }
    cout.flush();
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
