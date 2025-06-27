#include <ios>
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

// Counting Numbers
void solve()
{
    ll a, b;
    cin >> a >> b;

    auto sol = [&](ll lim) -> ll {
        string s = to_string(lim);
        int n = s.size();
        vector<vector<ll>> dp(n, vector<ll>(10));

        for (int i = 1; i < s[0]-'0'; ++i) {
            dp[0][i] = 1;
        }

        // only for digits of lim
        vector<bool> tight(n);
        tight[0] = 1;
        for (int i = 1; i < n; ++i)
            tight[i] = tight[i-1] and (s[i] != s[i-1]);

        for (int i = 1; i < n; ++i) {
            // when i-1 is one of the leading zeros
            for (int j = 1; j <= 9; ++j)
                dp[i][j]++;

            // unbounded no leading zeros
            for (int j1 = 0; j1 <= 9; ++j1) {
                for (int j2 = 0; j2 <= 9; ++j2) {
                    if (j1 != j2) {
                        dp[i][j2] += dp[i-1][j1];
                    }
                }
            }

            // when the digits align with digits of lim
            if (tight[i-1]) {
                for (int j = 0; j < (s[i] - '0'); ++j) {
                    if (j != (s[i-1] - '0')) {
                        dp[i][j]++;
                    }
                }
            }
        }

        ll sum = 0;
        if (tight[n-1])
            sum++;

        for (int i = 0; i <= 9; ++i) {
            sum += dp[n-1][i];
        }

        return sum;
    };

    a--;
    ll sola = a <= 10 ? a : sol(a);
    ll solb = b <= 10 ? b : sol(b);

    cout << solb - sola << '\n';
}

int T = 1;
int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // cin >> T;
    while(T--)
        solve();
    return 0;
}
