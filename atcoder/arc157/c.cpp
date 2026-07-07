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

#define assert(v) do { if (!(v)) { __builtin_trap(); } } while (0)

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

const int MOD = 998244353;
const int MAXN = 2005;
int paths[MAXN+1][MAXN+1];
int dp[MAXN+1][MAXN+1];

void precompute()
{
    paths[0][0] = 1;
    for (int i = 0; i <= MAXN; ++i) {
        for (int j = 0; j <= MAXN; ++j) {
            int i1 = i-1, j1 = j;
            for (int rep = 0; rep < 2; ++rep) {
                if (i1 >= 0 && j1 >= 0) {
                    paths[i][j] = (paths[i][j] + paths[i1][j1]) % MOD;
                }
                i1 = i, j1 = j-1;
            }
        }
    }
}

// ARC157C: YY Square
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<string> grid(n);
    for (int i = 0; i < n; ++i) {
        string s; cin >> s;
        grid[i] = s;
    }

    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i != 0 || j != 0)
                dp[i][j] = 0;

            int i1 = i-1, j1 = j;
            for (int rep = 0; rep < 2; ++rep) {
                if (i1 >= 0 && j1 >= 0) {

                    if (grid[i1][j1] == grid[i][j] && grid[i][j] == 'Y') {
                        dp[i][j] = (dp[i][j] + dp[i1][j1] + paths[i1][j1]) % MOD;
                        int r = n - 1 - i, c = m - 1 - j;
                        int pref_cnt = paths[i1][j1];
                        int suff_cnt = paths[r][c];
                        int c1 = ((2*dp[i1][j1]) % MOD * suff_cnt) % MOD;
                        int c2 = (pref_cnt * suff_cnt) % MOD;
                        ans = (ans + c1 + c2) % MOD;
                    } else {
                        dp[i][j] = (dp[i][j] + dp[i1][j1]) % MOD;
                    }
                }

                i1 = i, j1 = j-1;
            }
        }
    }

    cout << ans << '\n';
}

int T = 1;
int32_t main(void)
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    precompute();

    while(T--)
        solve();

    return 0;
}
