#include <iostream>
#include <queue>
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

#define xx first
#define yy second

// 1949I: Disks
void solve()
{
    using v2 = pair<ll, ll>;

    int n; cin >> n;
    vector<pair<v2, int>> vec(n);
    for (int i = 0; i < n; ++i) {  
        cin >> vec[i].first.xx >> vec[i].first.yy;
        cin >> vec[i].second;
    }

    vector<vector<int>> g(n);
    for (int i = 0; i < n; ++i) {
        v2 p0 = vec[i].xx; 
        ll r0 = vec[i].yy;
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;

            v2 p1 = vec[j].xx;
            ll r1 = vec[j].yy;

            ll sqrLen = (p1.xx - p0.xx)*(p1.xx - p0.xx) + (p1.yy - p0.yy)*(p1.yy - p0.yy);
            ll sqrRad = (r0 + r1)*(r0 + r1);
            if (sqrLen == sqrRad) {
                g[i].push_back(j);
            }
        }
    } 

    vector<int> id(n);
    bool ok = true;
    int ones = 0, twos = 0;
    function<void(int, int)> dfs = [&](int u, int p) {
        if (id[u] == 1) ones++;
        else twos++;

        for (int v: g[u]) {
            if (v == p) continue;

            if (id[v] == 0) {
                id[v] = 3 - id[u];
                dfs(v, u);
            } else if (id[v] == id[u]) {
                ok = false;
            }
        }
    };

    for (int i = 0; i < n; ++i) {
        if (id[i] != 0) continue;

        id[i] = 1;
        ok = true;
        ones = twos = 0;
        dfs(i, -1);

        // cerr << "DBG: " << i << ' ' << ones << ' ' << twos << '\n';
        if (ok && ones != twos) {
            cout << "YES\n";
            return;
        }
    }

    cout << "NO\n";
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
