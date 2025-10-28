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

// 1716C: Robot in a Hallway
void solve()
{
    int n; cin >> n;
    vector<vector<int>> a(2, vector<int>(n));
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> a[i][j];
        }
    }

    vector<int> dp(n), pd(n);
    vector<int> dp1(n), pd1(n);
    dp1[n-1] = dp[n-1] = 0;
    for (int i = n-2; i >= 0; --i) {
        dp[i] = max(a[0][i+1], dp[i+1] - 1);
        dp1[i] = max(a[1][i+1], dp1[i+1] - 1);
    }

    pd1[n-1] = pd[n-1] = 0;
    for (int i = n-2; i >= 0; --i) {
        pd[i] = max(a[1][i] - (n - 1 - i - 1), pd[i+1]);
        pd1[i] = max(a[0][i] - (n - 1 - i - 1), pd1[i+1]);
    }

    int ans = INT_MAX;
    int t = 0;
    for (int i = 0; i < n;) {
        {
            int t0 = t;
            t0 += max(0ll, dp[i] - t0) + (n - 1 - i);
            t0 += max(0ll, a[1][n-1] - t0) + 1;
            t0 += max(0ll, pd[i] - t0) + (n - 1 - i);
            ans = min(ans, t0);
        }

        if (i + 1 >= n) break;

        int x1 = a[1][i];
        int x2 = a[1][i + 1];
        int x3 = a[0][i + 1];

        t += max(0ll, x1 - t) + 1;
        t += max(0ll, x2 - t) + 1;

        {
            int t0 = t;
            t0 += max(0ll, dp1[i + 1] - t0) + (n - 1 - i - 1);
            t0 += max(0ll, a[0][n-1] - t0) + 1;
            t0 += max(0ll, pd1[i + 1] - t0) + (n - 1 - i - 1);
            ans = min(ans, t0);
        }

        t += max(0ll, x3 - t) + 1;
        i++;

        if (i + 1 >= n) {
            ans = min(ans, t);
            break;
        }

        int t1 = a[0][i + 1];
        t += max(0ll, t1 - t) + 1;
        i++;
    }

    cout << ans << '\n';
    cnt++;
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
