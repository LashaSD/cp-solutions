#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define xx first
#define yy second

const int mod = 998244353;
const int maxN = 305;
const int maxX = maxN * maxN;
int dp[maxN][maxX * 4 + 1];

// 1783D: Different Arrays
void solve()
{
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    dp[2][maxX + a[2] - a[1]] = 1;
    dp[2][maxX + a[2] + a[1]] = 1;

    for (int i = 2; i <= n-2; ++i) {
        int v2 = a[i+1];
        for (int x = 0; x <= 2*maxX; ++x) {
            if (dp[i][x] == 0) continue;

            int v1 = x - maxX;
            int a = v2 + v1, b = v2 - v1;
            dp[i+1][maxX + a] = (dp[i+1][maxX + a] + dp[i][x]) % mod;
            if (b != a) 
                dp[i+1][maxX + v2 - v1] = (dp[i+1][maxX + v2 - v1] + dp[i][x]) % mod;
        }
    }

    ll ans = 0;
    for (int j = 0; j <= 2*maxX; ++j) {
        ans = (ans + dp[n-1][j]) % mod;
        if (dp[n-1][j] > 0) {
            //cerr << "DBG: " << j - maxX << ' ' << dp[n-1][j] << '\n';
        }
    }

    cout << ans << '\n';
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
