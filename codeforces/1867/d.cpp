#include <iostream>
#include <cassert>
#include <climits>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <functional>

using namespace std;
using ll = long long;

#define int ll

// 1867D: Cyclic Operations
void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> b(n+1);
    for (int i = 1; i <= n; ++i) {
        cin >> b[i];
    }

    if (k == 1) {
        for (int i = 1; i <= n; ++i) {
            if (b[i] != i) {
                cout << "NO\n";
                return;
            }
        }

        cout << "YES\n";
        return;
    }

    vector<vector<int>> g(n+1);
    for (int i = 1; i <= n; ++i) {
        int u = i;
        int v = b[i];
        g[u].push_back(v);
    }

    int mn = INT_MAX, mx = INT_MIN;
    vector<int> e(n+1), l(n+1);
    int q = 1;
    function<void(int)> dfs = [&](int u) {
        e[u] = q;
        q++;

        for (int v: g[u]) {
            if (l[v] == 0 && e[v] > 0) {
                int len = e[u] - e[v] + 1;
                mn = min(mn, len);
                mx = max(mx, len);
            }

            if (e[v] == 0)
                dfs(v);
        }

        l[u] = q;
        q++;
    };

    for (int i = 1; i <= n; ++i) {
        int x = b[i];
        if (e[x] == 0)
            dfs(x);
    }

    cerr << mn << ' ' << mx << '\n';
    cout << ((mn == mx && mn == k) ? "YES\n" : "NO\n");
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
