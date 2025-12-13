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
#define xx first
#define yy second

// 2025D: Attribute Checks
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> vec(n);
    for (int i = 0; i < n; ++i) {
        cin >> vec[i];
    }

    vector<pair<int, int>> islands;
    for (int i = 0; i < n; ++i) {
        if (vec[i] != 0) {
            if (islands.size() > 0 && islands.back().yy == i-1)
                islands.back().yy = i;
            else
                islands.push_back(make_pair(i, i));
        }
    }

    vector<int> pref_zero(n);
    pref_zero[0] = vec[0] == 0;
    for (int i = 1; i < n; ++i) {
        pref_zero[i] = pref_zero[i-1] + (vec[i] == 0);
    }

    // vector<vector<int>> comp(islcnt, vector<int>(m + 1));
    int cnt = islands.size();
    vector<vector<int>> dp(m+1, vector<int>(m+1));
    for (int i = 0; i < cnt; ++i) {
        auto [l, r] = islands[i];
        vector<int> f1(m+1), f2(m+1);
        for (int j = l; j <= r; ++j) {
            if (vec[j] < 0)
                f1[-vec[j]]++;
            else
                f2[vec[j]]++;
        }

        for (int j = 1; j <= m; ++j) {
            f1[j] += f1[j-1];
            f2[j] += f2[j-1];
        }

        int lim = pref_zero[l];
        int new_zeros = n - r;
        if (i+1 < cnt)
            new_zeros = islands[i+1].xx - r - 1;

        for (int s = 0; s <= lim; ++s) {
            int intel = lim - s;
            int delta = f1[s] + f2[intel];
            dp[s][intel] += delta;
            for (int t = 0; t <= new_zeros; ++t) {
                int t1 = (new_zeros - t);
                if (s + t > m || intel + t1 > m) continue;

                dp[s + t][intel + t1] = max(dp[s + t][intel + t1], dp[s][intel]);
            }
        }
    }

    int ans = 0;
    int zeros = pref_zero[n-1];
    for (int i = 0; i <= zeros; ++i) {
        ans = max(ans, dp[i][zeros - i]);
    }

    cout << ans << '\n';
}

int T = 1;
int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // cin >> T;
    while(T--)
        solve();

    return 0;
}
