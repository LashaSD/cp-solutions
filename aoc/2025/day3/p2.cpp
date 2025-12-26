#include <bits/stdc++.h>

using namespace std;
using ll = long long;

signed main()
{
    vector<string> vec;
    while (cin >> vec.emplace_back());

    ll ans = 0;
    for (string& s: vec) {
        int n = s.size();
        if (n < 12) continue;

        vector<vector<int>> dp(n, vector<int>(13, -1));

        vector<int> pd(13, -1);
        for (int i = n-1; i >= 0; --i) {
            for (int k = 2; k <= 12; ++k) {
                int j = pd[k-1];
                if (j == -1) break;
                if (dp[i][k] == -1 || s[j] > s[dp[i][k]])
                    dp[i][k] = j;
            }

            dp[i][1] = i;
            for (int k = 1; k <= 12; ++k) {
                if (dp[i][k] >= 0 && (pd[k] == -1 || s[i] >= s[pd[k]]))
                    pd[k] = i;
            }
        }

        int mx = -1;
        for (int i = 0; i < n; ++i) {
            if (dp[i][12] >= 0 && (mx == -1 || s[i] > s[mx])) {
                mx = i;
            }
        }

        assert(mx >= 0);

        ll num = 0;
        int i = mx;
        for (int k = 12; k >= 1; i = dp[i][k], --k) {
            num += powl(10ll, k-1) * (s[i] - '0');
        }

        ans += num;
    }

    cout << ans << '\n';
}
