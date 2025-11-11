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

// 2028D: Alice's Adventures in Cards
void solve()
{
    int n; cin >> n;
    vector<vector<int>> vec(4, vector<int>(n + 1));
    for (int k = 1; k <= 3; ++k) {
        for (int i = 1; i <= n; ++i) {
            cin >> vec[k][i];
        }
    }

    static string players = "qkj";
    
    vector<pair<int, int>> to_n(n+1);
    int mn[4], idx[4];
    for (int k = 0; k <= 3; ++k)
        mn[k] = vec[k][n], idx[k] = n;

    for (int i = n-1; i >= 1; --i) {
        bool f = false;
        for (int k = 1; k <= 3; ++k) {
            if (vec[k][i] > mn[k]) {
                f = 1;
                to_n[i].xx = idx[k];
                to_n[i].yy = k;
            }
        }

        if (f)
        for (int k = 1; k <= 3; ++k) {
            if (vec[k][i] < mn[k]) {
                mn[k] = vec[k][i];
                idx[k] = i;
            }
        }
    }

    if (to_n[1].xx == 0) {
        cout << "NO\n";
        return;
    }

    vector<pair<int, int>> ans;
    int u = 1;
    while (u != n) {
        ans.push_back({to_n[u].yy, to_n[u].xx});
        u = to_n[u].xx;
    }

    cout << "YES\n";
    cout << ans.size() << '\n';
    for (auto [k, i]: ans) {
        cout << players[k - 1] << ' ' << i << '\n';
    }
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
