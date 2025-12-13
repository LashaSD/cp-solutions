#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using i32 = int32_t;
using u32 = uint32_t;

const int mod = 1e9 + 7;

#define int ll
#define xx first
#define yy second

vector<vector<int>> mult(const vector<vector<int>>& a, const vector<vector<int>>& b)
{
    int n = a.size();
    int s = a[0].size();
    int m = b[0].size();

    vector<vector<int>> res(n, vector<int>(m));
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
        if (p & 1) res = move(mult(res, base));
        base = move(mult(base, base));
        p >>= 1;
    }

    return res;
}

// Matrix Exponentiation:
// GYM102644G: Recurrence With Square
void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> a(n), c(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    for (int i = 0; i < n; ++i) {
        cin >> c[i];
    }

    int p, q, r;
    cin >> p >> q >> r;
    int N = n + 4;

    // [a_i, ... a_{i+n-1}, p, i, i^2, increment]
    vector<vector<int>> dp(1, vector<int>(N));
    for (int i = 0; i < n; ++i)
        dp[0][i] = a[i];

    const int P = n;
    const int I = n+1;
    const int I_SQ = n+2;
    const int INC = n+3;

    dp[0][P] = p;
    dp[0][I] = n; // index
    dp[0][I_SQ] = n*n; // index squared
    dp[0][INC] = 1; // index increment

    vector<vector<int>> mat(N, vector<int>(N));
    for (int i = 0; i < (n - 1); ++i) {
        mat[i+1][i] = 1;
    }

    for (int i = n; i < N; ++i) {
        mat[i][i] = 1;
    }

    // index
    mat[INC][I] = 1;

    // index squared
    mat[INC][I_SQ] = 1;
    mat[I][I_SQ] = 2;

    for (int i = 0; i < n; ++i) {
        mat[i][n-1] = c[n - i - 1];
    }

    mat[P][n-1] = 1;
    mat[I][n-1] = q;
    mat[I_SQ][n-1] = r;

    int dx = k - (n - 1);
    if (dx < 0) {
        cout << a[k] << '\n';
        return;
    }

    dp = move(mult(dp, binpow(mat, dx)));
    cout << dp[0][n-1] << '\n';
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
