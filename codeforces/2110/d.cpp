#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2110D: Fewer Batteries
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> vec(n+1);
    for (int i = 1; i <= n; ++i) {
        cin >> vec[i];
    }

    vector<vector<pair<int, int>>> g(n+1);

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
    }

    int l = 1, r = 1e9;
    vector<int> max(n+1);
    int ans = -1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        for (int i = 1; i <= n; ++i)
            max[i] = -1;

        max[1] = min(mid, vec[1]);
        for (int i = 1; i <= n; ++i) {
            if (max[i] == -1)
                continue;

            for (auto [v, w]: g[i]) {
                if (max[i] >= w) {
                    max[v] = min(mid, max[i] + vec[v]);
                }
            }
        }

        if (max[n] != -1) {
            if (ans == -1) {
                ans = max[n];
            } else {
                ans = min(ans, max[n]);
            }

            r = mid-1;
        } else {
            l = mid+1;
        }
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
