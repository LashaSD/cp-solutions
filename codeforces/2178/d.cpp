#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2178D: Xmas or Hysteria
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].xx;
        a[i].yy = i + 1;
    }

    sort(a.begin(), a.end());
    if (m > n/2) {
        cout << -1 << '\n';
        return;
    }

    vector<pair<int, int>> ans;
    if (m == 0) {
        int split = n-2;
        ll sum = 0;
        while (sum < a.back().xx && split >= 0) {
            sum += a[split].xx;
            split--;
        }

        if (sum < a.back().xx) {
            cout << -1 << '\n';
            return;
        }

        for (int i = 0; i <= split; ++i) {
            ans.push_back({a[i].yy, a[i+1].yy});
        }
        for (int i = split + 1; i < n-1; ++i) {
            ans.push_back({a[i].yy, a[n-1].yy});
        }
    } else {
        int rem = n - 2*m;
        for (int i = 0; i < rem; ++i) {
            ans.push_back({a[i].yy, a[i+1].yy});
        }
        for (int i = 0; i < m; ++i) {
            int l = rem + i;
            int r = rem + i + m;
            ans.push_back({a[r].yy, a[l].yy});
        }
    }

    cout << ans.size() << '\n';
    for (auto [x, y]: ans) {
        cout << x << ' ' << y << '\n';
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
