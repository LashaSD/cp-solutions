#include <iostream>
#include <cassert>
#include <climits>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <map>

using namespace std;
using ll = long long;

#define int ll

const int mod = 998244353;
const int maxN = 1e6; 
vector<vector<int>> primes(maxN + 1);

void precompute()
{
    for (int i = 2; i <= maxN; ++i) {
        if (primes[i].size() > 0) continue;

        for (int j = i; j <= maxN; j += i) {
            primes[j].push_back(i);
        }
    }
}

// 2037G: Natlan Exploring
void solve()
{
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<int> cnt(maxN + 1), dp(n);
    for (int i = 0; i < n; ++i) {
        int x = a[i];
        int m = primes[x].size();

        int maxMask = (1ll << m) - 1;
        int sum = 0;
        for (int mask = 1; mask <= maxMask; ++mask) {
            int c = 1;
            for (int j = 0; j < m; ++j) {
                int b = 1ll << j;
                if (b & mask) {
                    c *= primes[x][j];
                }
            }

            int k = __builtin_popcountll(mask);
            if (k % 2 == 0) {
                sum = (mod + (sum - cnt[c])) % mod;
            } else {
                sum = (sum + cnt[c]) % mod;
            }
        }

        if (i == 0) sum = 1;
        dp[i] = sum;

        for (int mask = 1; mask <= maxMask; ++mask) {
            int c = 1;
            for (int j = 0; j < m; ++j) {
                int b = 1ll << j;
                if (b & mask) {
                    c *= primes[x][j];
                }
            }

            cnt[c] = (cnt[c] + sum) % mod;
        }
    }

    cout << dp[n-1] << '\n';
}

int T = 1;
int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    precompute();

    // cin >> T;
    while(T--)
        solve();

    return 0;
}
