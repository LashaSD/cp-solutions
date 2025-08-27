#include <algorithm>
#include <bits/stdc++.h>
#include <utility>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

const int INF = 1e9;

// 1862F: Magic Will Save the World
void solve()
{
    int w, f;
    cin >> w >> f;
    int n; cin >> n;
    vector<int> vec(n);
    int sum = 0;
    for (int& x: vec) {
        cin >> x;
        sum += x;
    }

    vector<bool> dp(sum + 1);
    dp[0] = 1;
    for (int i = 0; i < n; ++i) {
        int x = vec[i];
        for (int w = sum; w - x >= 0; w--) {
            dp[w] = dp[w] || dp[w - x];
        }
    }

    int ans = 1e6;
    for (int i = 0; i <= sum; ++i) {
        if (!dp[i]) continue;

        int rest = sum - i;
        int ops_w = (i + w - 1) / w;
        int ops_f = ((sum - i) + f - 1) / f;
        ans = min(ans, max(ops_w, ops_f));
    }

    cout << ans << '\n';
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
