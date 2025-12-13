#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using i32 = int32_t;
using u32 = uint32_t;

#define int ll
#define xx first
#define yy second

const int inf = 2e18;

vector<vector<int>> mult(const vector<vector<int>>& a, const vector<vector<int>>& b)
{
    int n = a.size();
    int s = a[0].size();
    int m = b[0].size();

    vector<vector<int>> res(n, vector<int>(m, inf));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < s; ++k) {
                if (b[k][j] == inf || a[i][k] == inf) continue;
                res[i][j] = min(res[i][j], a[i][k] + b[k][j]);
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
        if (p & 1) res = move(mult(res, base));
        base = move(mult(base, base));
        p >>= 1;
    }

    return res;
}

// Matrix Exponentiation:
// GYM102644F: Min Path
void solve()
{
    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<int>> mat(n, vector<int>(n, inf));
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        mat[u - 1][v - 1] = w;
    }

    vector<vector<int>> dp(1, vector<int>(n, 0));

    dp = move(mult(dp, binpow(mat, k)));

    int ans = inf;
    for (int i = 0; i < n; ++i) {
        ans = min(ans, dp[0][i]);
    }

    if (ans == inf) {
        cout << "IMPOSSIBLE\n";
    } else {
        cout << ans << '\n';
    }
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
