#include <iostream>
#include <cassert>
#include <climits>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <map>

using namespace std;
using ll = long long;

#define int ll

// 2128D: Sum of LDS 
void solve()
{
    int n; cin >> n;
    vector<int> vec(n+1);
    for (int i = 1; i <= n; ++i) {
        cin >> vec[i];
    }

    vector<int> dp(n+1);
    vector<int> p(n+1);
    for (int i = 1; i <= n; ++i) {
        int prev = 0, j = 0;
        if (i > 1 && vec[i] <= vec[i-1]) {
            prev = max(prev, dp[i-1]);
            j = 1;
        }

        if (i > 2 && vec[i] <= vec[i-2]) {
            if (dp[i-2] > prev) j = 2;
            prev = max(prev, dp[i-2]);
        }

        p[i] = i - j;
        dp[i] = prev + 1;
    }

    vector<int> cnt(n+1);
    for (int i = n; i >= 1; --i) {
        if (p[i] != i)
            cnt[p[i]] += cnt[i] + 1;
    }

    vector<int> pref(n+1);
    for (int i = 1; i <= n; ++i) {
        pref[i] = pref[i-1] + dp[i];
    }

    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        int sum = pref[n] - pref[i-1];
        int delta = 0;

        int x = p[i], y = -1;
        if (i + 1 <= n) y = p[i+1];

        for (int rep = 0; rep < 2; ++rep) {
            int b = p[i-1] == x && x != i-1;
            if (x > 0 && x < i)
                delta += (cnt[x] - b)*dp[x];

            if (x == y) break;
            swap(x, y);
        }

        // cerr << "DBG: " << i << ' ' << ' ' << x << ' ' << y << ' ' << sum << ' ' << delta << '\n';
        ans += sum - delta;
    }

    cout << ans << '\n';
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
