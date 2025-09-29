#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll

const ll INF = 1e14;

// 2049D: Shift + Esc
void solve()
{
    int n, m, l;
    cin >> n >> m >> l;
    vector<vector<int>> grid(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> grid[i][j];
        }
    }

    vector<vector<int>> dp(n, vector<int>(m, INF));
    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < m; ++k) {
            vector<int> pd(m, INF);
            for (int j = 0; j < m; ++j) {
                int index = (j + k) % m;
                int cost = INF;

                if (i == 0 && j == 0)
                    cost = l*k + grid[i][index];

                if (i > 0)
                    cost = min(cost, l*k + grid[i][index] + dp[i-1][j]);

                if (j > 0)
                    cost = min(cost, grid[i][index] + pd[j-1]);

                pd[j] = cost;
            }

            for (int j = 0; j < m; ++j) {
                dp[i][j] = min(dp[i][j], pd[j]);
            }
        }
    }

    cout << dp[n-1][m-1] << '\n';
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
