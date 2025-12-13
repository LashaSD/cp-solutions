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

// Matrix Exponentiation:
// GYM102644B: String Mood
void solve()
{
    vector<vector<int>> a = {
        {19, 7}
    };

    vector<vector<int>> b = {
        {19, 7},
        {6, 20},
    };

    int n; cin >> n;
    if (n == 1) {
        cout << 19 << '\n';
        return;
    }

    vector<vector<int>> res = mult(a, binpow(b, n-1));
    cout << res[0][0] << '\n';
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

