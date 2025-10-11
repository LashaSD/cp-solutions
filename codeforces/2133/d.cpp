#include <iostream>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;
using ll = long long;

#define int ll

// 2133D: Chicken Jockey
void solve()
{
    int n; cin >> n;
    vector<int> vec(n+1);
    for (int i = 1; i <= n; ++i)
        cin >> vec[i];

    vector<int> dp(n+1);
    dp[1] = vec[1];
    for (int i = 2; i <= n; ++i) {
        dp[i] = min(dp[i-1] + vec[i] - 1, dp[i-2] + vec[i-1] + max(0ll, vec[i] - (i - 1)));
    }

    cout << dp[n] << '\n';
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
