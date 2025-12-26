#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 1510D: Digits
void solve()
{
    int n, d;
    cin >> n >> d;
    vector<int> a(n+1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    using ld = long double;
    vector<vector<ld>> dp(n+1, vector<ld>(10, 0));
    vector<vector<int>> pd(n+1, vector<int>(10, -1));
    for (int i = 1; i <= n; ++i) {
        if (log10(a[i]) > dp[i-1][(a[i] % 10)]) {
            dp[i][a[i] % 10] = log10(a[i]);
            pd[i][a[i] % 10] = -2;
        }

        for (int j = 0; j <= 9; ++j) {
            int c = (j*a[i]) % 10;
            ld x = dp[i-1][j];
            if (x == 0) continue;
            ld y = log10(a[i]);
            if (x + y > dp[i-1][c] && x + y > dp[i][c]) {
                dp[i][c] = x + y;
                pd[i][c] = j;
            }
        }

        for (int j = 0; j <= 9; ++j) {
            if (pd[i][j] == -1) {
                dp[i][j] = dp[i-1][j];
            }
        }
    }

    vector<int> ans;
    int d1 = d;
    int i = n;
    while (i >= 0) {
        if (pd[i][d1] == -1) {
            i--;
            continue;
        }

        ans.push_back(a[i]);
        d1 = pd[i][d1];
        i--;
        if (d1 == -2) break;
    }

    if (ans.empty()) {
        cout << -1  << '\n';
        return;
    }

    cout << ans.size() << '\n';
    for (int x: ans) {
        cout << x << ' ';
    }
    cout << '\n';
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
