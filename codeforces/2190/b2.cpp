#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <cstdint>
#include <set>
#include <cstdio>
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
const int N = 105;
int dp[N][N][N];
int pd[N][N][N];

// 2190B2: Sub-RBS (Hard Version)
void solve()
{
    int n; cin >> n;
    string s; cin >> s;
    vector<int> vec(n+1);
    for (int i = 1; i <= n; ++i) {
        vec[i] = s[i-1] == '(' ? 1 : -1;
    }

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            for (int k = 0; k <= n; ++k) {
                dp[i][j][k] = 0;
                pd[i][j][k] = 0;
            }
        }
    }

    // dp[x][len][k] = count of sequences such, that sum = x, size = len, leftmost -1 is at k.
    // k == 0 => no -1.
    dp[0][0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        // clear pd
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= n; ++j) {
                for (int k = 0; k <= n; ++k) {
                    pd[i][j][k] = 0;
                }
            }
        }

        for (int x = 0; x <= n; ++x) {
            for (int len = 1; len <= n; ++len) {
                for (int k = 0; k <= n; ++k) {
                    if (vec[i] == 1) {
                        if (x >= 1) {
                            pd[x][len][k] = (pd[x][len][k] + dp[x-1][len-1][k]) % MOD;
                        }
                    } else {
                        if (len == k) {
                            pd[x][len][k] = (pd[x][len][k] + dp[x+1][len-1][0]) % MOD;
                        } else if (k > 0) {
                            pd[x][len][k] = (pd[x][len][k] + dp[x+1][len-1][k]) % MOD;
                        }
                    }
                }
            }
        }

        // update dp with pd
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= n; ++j) {
                for (int k = 0; k <= n; ++k) {
                    dp[i][j][k] = (dp[i][j][k] + pd[i][j][k]) % MOD;
                }
            }
        }
    }

    ll ans = 0;
    for (int len = 2; len <= n; len += 2) {
        for (int k = 2; k <= len/2-1; ++k) {
            ll contrib = (dp[0][len][k] * (len-2)) % MOD;
            ans = (ans + contrib) % MOD;
        }
    }
    cout << ans << '\n';
}

int T = 1;
int32_t main(void)
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    cin >> T;
    while(T--)
        solve();

    return 0;
}


