#include <cstdio>
#include <cstdlib>
#include <functional>
#include <ios>
#include <iostream>
#include <set>
#include <algorithm>
#include <climits>
#include <cmath>
#include <vector>
#include <map>
#include <algorithm>
#include <bitset>
#include <cstdint>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

// C. Set Construction
void solve()
{
    int n; cin >> n;
    vector<string> matr(n);
    for (int i = 0; i < n; ++i) {
        cin >> matr[i];
    }

    vector<vector<int>> g(n, vector<int>());
    for (int i = 0; i < n; ++i) {
        const string& s = matr[i];
        for (int j = 0; j < s.length(); ++j) {
            if (s[j] == '1') {
                g[i].push_back(j);
            }
        }
    }

    vector<set<int>> ans(n);

    for (int i = 0; i < n; ++i) {
        ans[i].insert(i+1);
    }

    vector<bool> vis(n);
    function<void(int)> dfs = [&](int u) -> void {
        if (vis[u]) return;
        vis[u] = true;

        for (int v : g[u]) {
            dfs(v);
            for (int num : ans[u]) {
                ans[v].insert(num);
            }
        }
    };

    for (int u = 0; u < n; ++u) {
        dfs(u);
    }

    for (int i = 0; i < n; ++i) {
        cout << ans[i].size() << ' ';
        for (int num : ans[i]) {
            cout << num << ' ';
        }
        cout << '\n';
    }
    // cout << '\n';
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
