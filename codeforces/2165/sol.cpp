#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <cstdint>
#include <set>
#include <algorithm>
#include <functional>
#include <map>

#define assert(v) do { if (!(v)) { *(int*)0 = 0; } } while (0)

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

const int MOD = 998244353;

// 2165B Marble Council
void solve()
{
    int n; cin >> n;
    vector<int> vec(n+1), f(n+1);
    int mx = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> vec[i];
        f[vec[i]]++;
        if (f[vec[i]] > f[mx]) {
            mx = vec[i];
        }
    }

    vector<vector<int>> dp(n+1, vector<int>(n+1));
    for (int i = 0; i <= n; ++i)
        dp[i][0] = 1;

    for (int i = 1; i <= n; ++i) {
        if (f[i] == 0) {
            dp[i] = dp[i-1];
            continue;
        }

        for (int j = f[i]; j <= n; ++j) {
            dp[i][j] = (dp[i-1][j] + (dp[i-1][j - f[i]] * f[i]) % MOD) % MOD;
        }

        for (int j = 0; j < f[i]; ++j) {
            dp[i][j] = dp[i-1][j];
        }
    }

    ll ans = 0;
    for (int j = f[mx]; j <= n; ++j) {
        ans = (ans + dp[n][j]) % MOD;
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


