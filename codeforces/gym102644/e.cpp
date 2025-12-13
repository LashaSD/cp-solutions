#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using i32 = int32_t;
using u32 = uint32_t;

#define xx first
#define yy second

const int N = 8*8;

vector<vector<u32>> mult(const vector<vector<u32>>& a, const vector<vector<u32>>& b)
{
    i32 n = a.size();
    i32 s = a[0].size();
    i32 m = b[0].size();

    vector<vector<u32>> res(n, vector<u32>(m, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < s; ++k) {
                res[i][j] = res[i][j] + a[i][k] * b[k][j];
            }
        }
    }

    return res;
}

vector<vector<u32>> binpow(vector<vector<u32>> base, int p)
{
    int n = base.size();
    vector<vector<u32>> res(n, vector<u32>(n));
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

// Matrix Exponentiation:
// GYM102644E: Knight Paths
void solve()
{
    int k; cin >> k;

    const vector<pair<int, int>> offsets = {
        {-2, -1},
        {-2,  1},
        {2, -1},
        {2,  1},
        {-1, 2},
        {-1, -2},
        {1, 2},
        {1, -2},
    };

    vector<vector<u32>> mat(N + 1, vector<u32>(N + 1));
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            for (auto [di, dj]: offsets) {
                int i1 = i + di, j1 = j + dj;
                if (i1 < 0 || i1 >= 8 || j1 < 0 || j1 >= 8) continue;
                mat[8*i1 + j1][8*i + j] = 1;
            }
        }
    }

    for (int i = 0; i <= N; ++i) {
        mat[i][N] = 1;
    }

    vector<vector<u32>> dp(1, vector<u32>(N + 1));
    dp[0][0] = 1;

    dp = mult(dp, binpow(mat, k + 1));
    cout << dp[0][N] << '\n';
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
