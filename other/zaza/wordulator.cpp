#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve()
{
    string s1, s2;
    cin >> s2 >> s1;
    int n = s1.size();
    int m = s2.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (s1[i-1] == s2[j-1]) {
                dp[i][j] = max({dp[i-1][j-1] + 1, dp[i-1][j], dp[i][j-1]});
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }

    int add_cnt = 0;
    int rem_cnt = 0;
    int right_most = 0;

    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (s1[i-1] == s2[j-1]) {
            i--;
            j--;
        } else if (dp[i-1][j] > dp[i][j-1]) {
            right_most = max(right_most, dp[i][j]);
            add_cnt++;
            i--;
        } else {
            right_most = max(right_most, dp[i][j]);
            rem_cnt++;
            j--;
        }
    }
    
    add_cnt += i;
    rem_cnt += j;

    cout << (rem_cnt + add_cnt) * 10 + right_most * 2 << '\n';
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
