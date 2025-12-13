#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2153D: Not Alone
void solve()
{
    int n; cin >> n;
    vector<int> a(n+1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    const int inf = LLONG_MAX >> 2;
    vector<int> dp(n+1);
    int ans = inf;
    for (int rep = 0; rep < 3; ++rep) {
        dp.assign(n+1, inf);
        dp[0] = 0;
        for (int i = 1; i <= n - 1; ++i) {
            int ops = abs(a[i] - a[i+1]);
            dp[i+1] = min(dp[i+1], dp[i-1] + ops);
            
            if (i + 2 <= n) {
                int mx = max({a[i], a[i+1], a[i+2]});
                int mn = min({a[i], a[i+1], a[i+2]});
                ops = mx - mn;
                dp[i+2] = min(dp[i+2], dp[i-1] + ops);
            }
        }

        ans = min(ans, dp[n]);

        if (rep == 0)
            rotate(a.begin() + 1, a.begin() + 2, a.end());
        else
            rotate(a.begin() + 1, a.begin() + n - 1, a.end());
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
