#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2038K: Grid Walk
void solve()
{
    int n, a, b;
    cin >> n >> a >> b;
    vector<int> row(n+1), col(n+1);
    for (int i = 1; i <= n; ++i) {
        row[i] = __gcd(i, a);
        col[i] = __gcd(i, b);
    }

    int r = n, c = n;
    while (r >= 1 && row[r] != 1) r--;
    while (c >= 1 && col[c] != 1) c--;

    int s = 0;
    for (int i = 1; i <= c-1; ++i) {
        s += row[1] + col[i];
    }

    for (int i = 1; i <= r - 1; ++i) {
        s += row[i] + col[c];
    }

    int rown = n - r + 1;
    int coln = n - c + 1;
    vector<vector<int>> grid(rown + 1, vector<int>(coln + 1));
    for (int i = r; i <= n; ++i) {
        for (int j = c; j <= n; ++j) {
            grid[i - r + 1][j - c + 1] = row[i] + col[j];
        }
    }
    
    const int inf = 1e9;
    vector<vector<int>> dp(rown + 1, vector<int>(coln + 1, inf));
    dp[1][1] = grid[1][1];
    for (int i = 1; i <= rown; ++i) {
        for (int j = 1; j <= coln; ++j) {
            if (i > 1)
                dp[i][j] = min(dp[i][j], dp[i-1][j] + grid[i][j]);

            if (j > 1)
                dp[i][j] = min(dp[i][j], dp[i][j-1] + grid[i][j]);
        }
    }

    cout << dp[rown][coln] + s << '\n';
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
