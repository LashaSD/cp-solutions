#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

const ll MOD = 998244353;

// 2091F: Igor and Mountain
void solve()
{
    int n, m, d;
    cin >> n >> m >> d;
    vector<string> grid(n);
    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
    }

    vector<ll> pref(m+1);
    for (int i = 1; i <= m; ++i)
        pref[i] = pref[i-1] + (grid[0][i-1] == 'X');

    vector<ll> ans(m+1);
    for (int i = 0; i < m; ++i) {
        if (grid[0][i] != 'X') {
            ans[i+1] = ans[i];
            continue;
        }

        int center = i + 1;
        int left = max(1, center - d), right = min(m, center + d);
        ans[i+1] = ((ans[i] % MOD) + ((pref[right] - pref[left-1]) % MOD)) % MOD;
    }

    vector<ll> loc_ans(m+1);
    vector<ll> loc_loc_ans(m+1, 0);

    for (int i = 1; i < n; ++i) {
        for (ll& x: loc_ans) x = 0;
        for (ll& x: loc_loc_ans) x = 0;

        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == '#') {
                loc_ans[j+1] = loc_ans[j];
                continue;
            }

            int center = j+1;
            int half_len = max(0, d - 1);
            int left = max(1, center - half_len), right = min(m, center + half_len);
            ll sum = (MOD + ans[right] - ans[left-1]) % MOD;
            loc_ans[j+1] = ((loc_ans[j] % MOD) + (sum % MOD)) % MOD;
        }

        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == '#') {
                loc_loc_ans[j+1] = loc_loc_ans[j];
                continue;
            };

            int center = j+1;
            int half_len = d;
            int left = max(1, center - half_len), right = min(m, center + half_len);
            ll right_segment = (MOD + (loc_ans[right] - loc_ans[center])) % MOD;
            ll left_segment = (MOD + (loc_ans[center-1] - loc_ans[left-1])) % MOD;
            ll center_value = (MOD + (loc_ans[center] - loc_ans[center-1])) % MOD;
            ll sum = (left_segment + right_segment) % MOD;
            loc_loc_ans[j+1] = ((loc_loc_ans[j] % MOD) + ((sum + center_value) % MOD)) % MOD;
        }

        ans = loc_loc_ans;
    }

    cout << ans.back() << '\n';
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
