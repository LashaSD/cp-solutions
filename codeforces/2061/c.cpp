#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

const int MOD = 998244353;

// 2061C: Kevin and Puzzle
void solve()
{
    int n; cin >> n;
    vector<int> vec(n);
    for (int i = 0; i < n; ++i) {
        cin >> vec[i];
    }

    auto liar = [&](int i) {
        return (i + 1) / 2 < vec[i];
    };

    vector<vector<int>> dp(n, vector<int>(2));
    dp[0][0] = vec[0] == 0;
    dp[0][1] = 1;
    for (int i = 1; i < n; ++i) {
        // [i] is honest
        if (!liar(i)) {
            // [i-1] is honest
            if (vec[i-1] == vec[i]) {
                dp[i][0] = (dp[i][0] + dp[i-1][0]) % MOD;
            }

            // [i-1] is a liar
            if (
                vec[i] > 0
                && (i < 2 || vec[i-2] + 1 == vec[i])
            ) {
                dp[i][0] = (dp[i][0] + dp[i-1][1]) % MOD;
            }
        }

        dp[i][1] = dp[i-1][0];
    }

    cout << (dp[n-1][0] + dp[n-1][1]) % MOD << '\n';
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
