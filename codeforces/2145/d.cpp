#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <cstdint>
#include <set>
#include <algorithm>
#include <assert.h>
#include <functional>
#include <map>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

const int maxn = 30;
int dp[maxn + 5][maxn * maxn + 5];

void precompute()
{
    dp[2][1] = 1;
    for (int n = 3; n <= maxn; ++n) {
        for (int k = 1; k <= n * (n - 1) / 2; ++k) {
            for (int i = 1; i <= n-1; ++i) {
                int contrib = i * (n - i);
                if (contrib == k) {
                    dp[n][k] = i;
                    break;
                }

                if (contrib > k) continue;

                if (dp[n - i][k - contrib] > 0) {
                    dp[n][k] = i;
                    break;
                }
            }
        }
    }
}

// 2145D: Inversion Value of a Permutation
void solve()
{
    int n, k;
    cin >> n >> k;
    if (k == 0) {
        for (int i = 1; i <= n; ++i) {
            cout << i << ' ';
        }
        cout << '\n';
        return;
    }

    if (dp[n][k] == 0) {
        cout << 0 << '\n';
        return;
    }

    int len = n;
    vector<int> segments;
    segments.push_back(0);
    int offset = 0;
    while (k > 0) {
        int i = dp[n][k];
        int contrib = i * (n - i);
        segments.push_back(offset + i);
        k -= contrib;
        n -= i;
        offset += i;
    }
    segments.push_back(len);

    vector<int> ans(len+1);
    int current = 1;
    for (int i = (int)segments.size() - 2; i >= 0; --i) {
        int l = segments[i], r = segments[i+1];
        for (int j = l+1; j <= r; ++j) {
            ans[j] = current++;
        }
    }

    for (int i = 1; i <= len; ++i) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
}

int T = 1;
int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    precompute();

    cin >> T;
    while(T--)
        solve();

    return 0;
}
