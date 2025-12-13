#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

const int mod = 1e9 + 7;

vector<vector<int>> mult(const vector<vector<int>>& a, const vector<vector<int>>& b)
{
    int n = a.size();
    int s = a[0].size();
    int m = b[0].size();

    vector<vector<int>> res(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < s; ++k) {
                res[i][j] = (res[i][j] + ((a[i][k] * b[k][j]) % mod)) % mod;
            }
        }
    }

    return res;
}

vector<vector<int>> binpow(vector<vector<int>> base, int p)
{
    vector<vector<int>> res;
    while (p > 0) {
        if (p & 1) {
            if (res.size() == 0) res = base;
            else res = mult(res, base);
        }

        base = mult(base, base);
        p >>= 1;
    }

    return res;
}

// 1117D: Magic Gems
void solve()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> dp(1, vector<int>(m, 1));
    dp[0][m-1] += 1;

    vector<vector<int>> mat(m, vector<int>(m));
    for (int i = 0; i < m-1; ++i) {
        mat[i][i+1] = 1;
    }

    mat[m-1][0] = 1;
    mat[m-1][m-1] = 1;
    int dx = n - m;

    if (dx <= 0) {
        cout << dp[0][n - 1] << '\n';
        return;
    }

    vector<vector<int>> res = mult(dp, binpow(mat, dx));
    cout << res[0][m - 1] << '\n';
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
