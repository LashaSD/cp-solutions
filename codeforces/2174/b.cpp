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

#define assert(v) do { if (!(v)) { *(int*)0 = 0; } } while (0)

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2174B: Wishing Cards
void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> vec(n+1);
    for (int i = 1; i <= n; ++i) {
        cin >> vec[i];
    }

    vector<int> indices;
    int mx = -1;
    for (int i = 1; i <= n; ++i) {
        if (vec[i] > mx) {
            mx = vec[i];
            indices.push_back(i);
        }
    }

    ll ans = 0;
    vector<vector<int>> dp(k+1, vector<int>(k+1));
    for (int idx = 0; idx < (int)indices.size(); ++idx) {
        int i = indices[idx];
        int last_bound = idx > 0 ? vec[indices[idx-1]] : 0;
        int d = n - i + 1;
        for (int mx = vec[i]; mx > last_bound; --mx) {
            for (int cnt = mx; cnt <= k; ++cnt) {
                for (int pmx = last_bound; pmx >= 0; --pmx) {
                    dp[cnt][mx] = max(dp[cnt][mx], dp[cnt - mx][pmx] + (mx - pmx) * d);
                    ans = max(ans, dp[cnt][mx]);
                }
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

    cin >> T;
    while(T--)
        solve();

    return 0;
}
