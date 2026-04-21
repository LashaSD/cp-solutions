#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2167G: Mukhammadali and the Smooth Array
void solve()
{
    int n; cin >> n;
    vector<int> vec(n), cost(n);

    for (int i = 0; i < n; ++i) {
        cin >> vec[i];
    }

    for (int i = 0; i < n; ++i) {
        cin >> cost[i];
    }

    vector<int> dp(n), pd(n);
    for (int i = 1; i < n; ++i) {
        int x = LLONG_MAX;
        int accum = 0;
        for (int j = i-1; j >= 0; --j) {
            if (vec[j] > vec[i]) {
                accum += cost[j];
                continue;
            }

            x = min(x, accum + pd[j]);
            accum += cost[j];
        }
        x = min(x, accum);
        pd[i] = x;
        dp[i] = min(dp[i-1] + cost[i], x);
    }

    cout << dp[n-1] << '\n';
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
