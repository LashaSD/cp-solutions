#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;
#define int ll

const int MOD = 998244353;

// ARC179B: Between B and B
void solve()
{
    int m, n;
    cin >> m >> n;
    vector<int> x(m + 1);
    for (int i = 1; i <= m; ++i)
        cin >> x[i];

    vector<vector<int>> inv_x(m+1);

    for (int i = 1; i <= m; ++i) {
        inv_x[x[i]].push_back(i);
    }

    int max_mask = 0;
    for (int i = 1; i <= m; ++i) {
        max_mask |= (1 << (i-1));
    }

    vector<vector<ll>> dp(n + 5, vector<ll>(max_mask + 1));
    dp[1][max_mask] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int mask = 1; mask <= max_mask; mask++) {
            for (int num = 1; num <= m; ++num) {
                int it = (1 << (num-1));
                bool turned_on = (mask & it) != 0;
                if (turned_on) {
                    int newmask = mask;
                    // turn off it
                    newmask ^= it;
                    for (int u: inv_x[num]) {
                        int umask = (1 << (u - 1));
                        newmask |= umask;
                    }

                    dp[i+1][newmask] = ((dp[i+1][newmask] % MOD) + (dp[i][mask] % MOD)) % MOD;
                }
            }
        }
    }

    ll ans = 0;
    for (int i = 1; i <= max_mask; ++i)
        ans = ((ans % MOD) + ((dp[n][i] % MOD) % MOD) * (__builtin_popcount(i) % MOD)) % MOD;
    cout << ans << '\n';
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
