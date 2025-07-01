#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

// 1580A Portal
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<bool>> grid(n, vector<bool>(m));
    for (int i = 0; i < n; ++i) {
        string s; cin >> s;
        for (int j = 0; j < m; ++j) {
            grid[i][j] = s[j] - '0';
        }
    }

    // precompute column prefix sum
    vector<vector<int>> pref(m, vector<int>(n));
    for (int j = 0; j < m; ++j) {
        pref[j][0] = grid[0][j];
        for (int i = 1; i < n; ++i) {
            pref[j][i] = pref[j][i-1] + grid[i][j];
        }
    }

    auto count_ones = [&](int i1, int i2, int j) {
        return pref[j][i2] - pref[j][i1];
    };

    auto count_zeros = [&](int i1, int i2, int j) {
        return i2 - i1 - count_ones(i1, i2, j);
    };

    int ans = INT_MAX;
    for (int i1 = 0; i1 < n; ++i1) {
        for (int i2 = i1+4; i2 < n; ++i2) {
            vector<int> dp(m, 0), running_dp(m, INT_MAX);
            // dp[i] = dp[i-1] - num_of_middle_zeros + num_of_middle_ones + num_of_extreme_zeros + num_of_i'th middle zeros

            // returns sum of contributions of first three columns from j, j being the starter column
            auto first_three = [&] (int j) -> int {
                return count_zeros(i1, i2-1, j) +
                    (1-grid[i1][j+1] + count_ones(i1, i2-1, j+1) + 1-grid[i2][j+1]) +
                    (1-grid[i1][j+2] + count_ones(i1, i2-1, j+2) + 1-grid[i2][j+2]);
            };
            dp[3] = first_three(0) + count_zeros(i1, i2-1, 3);

            for (int j = 4; j < m; ++j) {
                int last_mid_zeroes = count_zeros(i1, i2-1, j-1);
                int last_mid_ones = count_ones(i1, i2-1, j-1);
                int last_corner_zeroes = (1-grid[i1][j-1]) + (1-grid[i2][j-1]);
                int curr_mid_zeros = count_zeros(i1, i2-1, j);
                dp[j] = dp[j-1] - last_mid_zeroes + last_mid_ones + last_corner_zeroes + curr_mid_zeros;
            }

            running_dp[m-1] = dp[m-1];
            for (int j = m-2; j >= 3; j--) {
                running_dp[j] = min(running_dp[j+1], dp[j]);
            }

            ans = min(ans, running_dp[3]);
            int deduction = count_zeros(i1, i2-1, 0);
            for (int j = 1; j <= (m-4); ++j) {
                // CHECK AGAIN
                int current_contrib = (1-grid[i1][j]) + (1-grid[i2][j]) + count_ones(i1, i2-1, j);
                deduction += current_contrib;
                int current_new_contrib = count_zeros(i1, i2-1, j);
                int range_contrib = running_dp[j+3] - deduction + current_new_contrib;
                ans = min(ans, range_contrib);
            }
        }
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
