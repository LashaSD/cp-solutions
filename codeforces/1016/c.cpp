#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = unsigned long long;

// 1016C: Vasya And The Mushrooms
void solve()
{
    int n; cin >> n;
    vector<vector<ll>> vec(2, vector<ll>(n));
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> vec[i][j];
        }
    }

    vector<vector<ll>> suff(2, vector<ll>(n+1)), pref(2, vector<ll>(n+1));
    for (int i = 0; i < 2; ++i) {
        suff[i][n-1] = vec[i][n-1];
        for (int j = n-2; j >= 0; --j) {
            suff[i][j] = vec[i][j] + suff[i][j+1];
        }

        pref[i][0] = vec[i][0];
        for (int j = 1; j < n; ++j) {
            pref[i][j] = vec[i][j] + pref[i][j-1];
        }
    }

    array<pair<ll, ll>, 2> sum;
    for (int i = 0; i < 2; ++i) {
        sum[i].first = 0;
        for (int j = 1; j < n; ++j) {
            sum[i].first += vec[i][j] * j;
        }

        sum[i].second = 0;
        for (int j = n-2; j >= 0; --j) {
            sum[i].second += vec[i][j] * (n - j - 1);
        }
    }

    ll ans = sum[0].first + sum[1].second + (suff[1][0] * n);
    ll trail_sum = 0;
    for (int i = 0; i < n; ++i) {
        bool going_down = (i % 2 == 0);

        ll top = vec[0][i];
        ll bot = vec[1][i];

        ll loc_ans = 0;
        if (going_down) {
            ll bot_sum = suff[1][i];
            ll top_sum = suff[0][i+1];
            int index = (i * 2);

            ll bot_prod_sum = sum[1].first + (bot_sum * (index + 1));
            sum[0].first -= suff[0][i+1];
            sum[1].first -= suff[1][i+1];

            sum[1].second -= (bot * (n-i-1));
            sum[0].second -= (top * (n - i - 1));
            ll top_prod_sum = sum[0].second + top_sum * (n - i + index + 1);

            loc_ans = trail_sum + top * index + bot_prod_sum + top_prod_sum;
            trail_sum += top * index + bot * (index + 1);
        } else {
            ll bot_sum = suff[1][i+1];
            ll top_sum = suff[0][i];
            int index = (i * 2);

            ll top_prod_sum = sum[0].first + (top_sum * (index + 1));
            dbg(index);
            dbg(top_prod_sum);
            sum[0].first -= suff[0][i+1];
            sum[1].first -= suff[1][i+1];

            sum[1].second -= (bot * (n-i-1));
            sum[0].second -= (top * (n-i-1));
            ll bot_prod_sum = sum[1].second + bot_sum * (n - i + index + 1);
            dbg(sum[1].second);
            dbg(bot_prod_sum);

            loc_ans = trail_sum + bot * index + top_prod_sum + bot_prod_sum;
            trail_sum += bot * index + top * (index + 1);
        }

        dbg(loc_ans);
        ans = max(ans, loc_ans);
    }

    ans = max(ans, trail_sum);
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
