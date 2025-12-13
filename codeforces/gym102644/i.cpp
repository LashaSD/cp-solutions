#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

const int mod = 1e9 + 7;
using Mat = vector<vector<int>>;

static inline Mat mult(const Mat& a, const Mat& b)
{
    int n = a.size();
    int s = a[0].size();
    int m = b[0].size();

    Mat res(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) { 
            for (int k = 0; k < s; ++k) {
                res[i][j] = (res[i][j] + (a[i][k]*b[k][j] % mod)) % mod;
            }
        }
    }

    return res;
}

// Matrix Exponentiation:
// GYM102644I: Count Paths Queries
void solve()
{
    int n, m, q;
    cin >> n >> m >> q;
    Mat mat(n, vector<int>(n));
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        mat[u - 1][v - 1] = 1;
    }

    Mat id(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        id[i][i] = 1;

    vector<Mat> pows(32);
    pows[0] = id;
    pows[1] = mat;
    for (int i = 2; i < 32; ++i) { 
        pows[i] = mult(pows[i-1], pows[i-1]);
    }

    Mat dp(1, vector<int>(n));
    for (int qi = 0; qi < q; ++qi) {
        int s, t, k;
        cin >> s >> t >> k;

        Mat new_dp = dp;
        new_dp[0].assign(n, 0);
        new_dp[0][s-1] = 1;

        for (int b = 1; k > 0; ++b, k >>= 1) {
            if (k & 1)
                new_dp = mult(new_dp, pows[b]);
        }

        cout << new_dp[0][t - 1] << '\n';
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
