#include <iostream>
#include <cassert>
#include <climits>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <functional>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 1359D: Yet Another Yet Another Task
void solve()
{
    int n; cin >> n;
    vector<int> vec(n+1);
    for (int i = 1; i <= n; ++i) {
        cin >> vec[i];
    }

    int ans = 0;
    vector<int> dp(n+1);
    for (int k = 0; k <= 30; ++k) {
        for (int i = 1; i <= n; ++i) {
            if (vec[i] < 0)
                dp[i] = dp[i-1] + vec[i];
            else if (vec[i] > k)
                dp[i] = 0;
            else
                dp[i] = max(dp[i-1] + vec[i], vec[i]);
        }

        for (int i = 1; i <= n; ++i) {
            ans = max(ans, dp[i] - k);
        }
    }

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
