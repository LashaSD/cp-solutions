#include <bits/stdc++.h>

#pragma GCC optimize("unroll-loops")
using namespace std;
using ll = long long;

#define xx first
#define yy second

ll mat[70][48][48];
int matn = 0;

static inline int mul(int A, int B)
{
    int C = matn++;
    for (int i = 0; i < 48; ++i) {
        for (int k = 0; k < 48; ++k) {
            for (int j = 0; j < 48; ++j) {
                mat[C][i][j] += mat[A][i][k] * mat[B][k][j];
            }
        }
    }
    return C;
}

int binpow(int A, int p)
{
    int res = matn++;
    for (int i = 0; i < 48; ++i) {
        mat[res][i][i] = 1;
    }

    while (p > 0) {
        if (p & 1) res = mul(res, A);
        A = mul(A, A);
        p >>= 1;
    }

    return res;
}

// 1912J: Joy of Pokémon Observation 
void solve()
{
    int t = 0, m = 0;
    cin >> t >> m;
    vector<int> l(m+1);
    for (int i = 1; i <= m; ++i) {
        cin >> l[i];
    }

    vector<vector<ll>> dp(4, vector<ll>(17));
    dp[0][0] = 1;
    for (int i = 1; i <= 16; ++i) {
        for (int j = 1; j <= m; ++j) {
            for (int k = 0; k <= j; ++k) {
                if (i - l[j] < 0) continue;
                dp[j][i] += dp[k][i-l[j]];
            }
        }
    }

    if (t <= 16) {
        cout << dp[0][t] + dp[1][t] + dp[2][t] + dp[3][t] << '\n';
        return;
    }

    int A = matn++;
    mat[A][16 - l[1]][15] = 1;
    if (m >= 2) {
        mat[A][1*16 - l[2]][16 + 15] = 1;
        mat[A][2*16 - l[2]][16 + 15] = 1;
    }

    if (m >= 3) {
        mat[A][1*16 - l[3]][32 + 15] = 1;
        mat[A][2*16 - l[3]][32 + 15] = 1;
        mat[A][3*16 - l[3]][32 + 15] = 1;
    }

    for (int k = 0; k < m; ++k) {
        for (int i = k*16; i < ((k+1)*16) - 1; ++i) {
            mat[A][i+1][i] = 1;
        }
    }

    vector<ll> dp1(16*3), dp2(16*3);
    for (int i = 1; i <= 3; ++i) {
        for (int j = 1; j <= 16; ++j) {
            dp1[(i-1)*16 + j - 1] = dp[i][j];
        }
    }

    int T = binpow(A, t - 16);
    for (int k = 0; k < 48; ++k) {
        for (int j = 0; j < 48; ++j) {
            dp2[j] += dp1[k] * mat[T][k][j];
        }
    }

    cout << dp2[15] + dp2[16 + 15] + dp2[32 + 15] << '\n';

    for (int i = 0; i < matn; ++i) {
        for (int j = 0; j < 48; ++j) {
            for (int k = 0; k < 48; ++k) {
                mat[i][j][k] = 0;
            }
        }
    }
    matn = 0;
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

