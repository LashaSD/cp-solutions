#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2073J: Gathering Sharks
void solve()
{
    int n; cin >> n;
    vector<int> a(n+1);
    for (int i = 1; i <= n; ++i) {
        int x; cin >> x;
        a[x] = i;
    }

    const int inf = LLONG_MAX >> 3;
    vector<vector<int>> dp(n+1, vector<int>(n+1, inf));
    for (int x = 1; x <= n; ++x)
        dp[x][0] = 0;

    for (int x = n; x >= 1; --x) {
        for (int s = 1; x + s <= n; ++s) {
            for (int j = 0; j < s; ++j) {
                int y = x + j + 1;
                int s2 = s - j - 1;
                int cost = dp[x][j] + (dp[y][s2] + abs(a[x] - a[y]));
                dp[x][s] = min(dp[x][s], cost);
            }
        }
    }

    cout << dp[1][n - 1] << '\n';
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
