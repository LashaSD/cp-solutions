#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int INF = 1e9;

// ABC419E: Subarray Sum Divisibility
void solve()
{
    int n, m, l;
    cin >> n >> m >> l;

    vector<int> vec(n);
    for (int& x: vec)
        cin >> x;

    vector<vector<int>> dp(l+1, vector<int>(m, INF));
    dp[0][0] = 0;
    for (int i = 1; i <= l; ++i) {
        for (int j = 0; j < m; ++j) {
            int ops = 0;
            for (int k = i; k <= n; k += l) {
                int loc_ops = j - vec[k-1];
                if (loc_ops < 0) loc_ops += m;
                ops += loc_ops;
            }

            for (int k = 0; k < m; ++k) {
                dp[i][(j+k)%m] = min(dp[i][(j+k)%m], dp[i-1][k] + ops);
            }
        }
    }

    cout << dp[l][0] << '\n';
}

int T = 1;
int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //cin >> T;
    while(T--)
        solve();
    return 0;
}
