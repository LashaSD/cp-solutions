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

    vector<vector<int>> res(n, vector<int>(m, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < s; ++k) {
                res[i][j] = (res[i][j] + a[i][k] * b[k][j] % mod) % mod;
            }
        }
    }

    return res;
}

vector<vector<int>> binpow(vector<vector<int>> base, int p)
{
    int n = base.size();
    vector<vector<int>> res(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        res[i][i] = 1;
    }

    while (p > 0) {
        if (p & 1) res = mult(res, base);
        base = mult(base, base);
        p >>= 1;
    }

    return res;
}

// Matrix Exponentiation
// GYM102644D: Count Paths
void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> mat(n, vector<int>(n));
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        mat[u - 1][v - 1] = 1;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cerr << mat[i][j] << ' ';
        }
        cerr << '\n';
    }

    vector<vector<int>> dp(1, vector<int>(n, 1));

    dp = mult(dp, binpow(mat, k));

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans = (ans + dp[0][i]) % mod;
    }

    cout << ans << '\n';
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
