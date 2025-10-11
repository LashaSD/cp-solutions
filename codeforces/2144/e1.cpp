#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll

const int mod = 998244353;

ll binpow(ll a, ll b) 
{
    ll res = 1;
    a = a % mod;
    while (b > 0){
        if ((b & 1) != 0){
            res = (res * a) % mod;
        }

        a = (a * a) % mod;
        b >>= 1LL;
    }
    return res;
}

// 2144E1: Looking at Towers (easy version)
void solve()
{
    int n; cin >> n;
    vector<int> vec(n);
    for (int& x: vec)
        cin >> x;

    vector<int> pref(n), suff(n);
    suff.back() = vec.back();
    pref[0] = vec[0];

    vector<int> l_side = { 0 }, r_side = { 0 };
    for (int i = 0; i < n; ++i) {
        if (vec[i] > l_side.back()) {
            l_side.push_back(vec[i]);
        }
    }

    for (int i = n-1; i >= 0; --i) {
        if (vec[i] > r_side.back()) {
            r_side.push_back(vec[i]);
        }
    }

    int mx_num = 0;
    for (int x: vec)
        mx_num = max(mx_num, x);

    int m = l_side.size();
    vector<vector<int>> dp(n, vector<int>(m));
    vector<int> accum(m);
    for (int i = 0; i < n; ++i) {
        int x = vec[i];

        if (x == vec.front()) dp[i][0]++;

        auto it = lower_bound(l_side.begin(), l_side.end(), x);
        int idx = it - l_side.begin() - 1;

        if (*it == x && x != vec.front()) {
            dp[i][idx] = (dp[i][idx] + accum[idx - 1]) % mod;
        }

        for (int k = idx; k < m && i > 0; ++k) {
            dp[i][k] = (accum[k] + dp[i][k]) % mod;
        }

        for (int k = 0; k < m && vec[i] != mx_num; ++k) {
            accum[k] = (accum[k] + dp[i][k]) % mod;
        }
    }

    m = r_side.size();
    vector<vector<int>> pd(n, vector<int>(m));

    accum.resize(m, 0);
    for (int& x: accum) x = 0;

    for (int i = n-1; i >= 0; --i) {
        int x = vec[i];

        if (x == vec.back()) pd[i][0]++;

        auto it = lower_bound(r_side.begin(), r_side.end(), x);
        int idx = it - r_side.begin() - 1;

        if (*it == x && x != vec.back()) {
            pd[i][idx] = (pd[i][idx] + accum[idx - 1]) % mod;
        }

        for (int k = idx; k < m && i > 0; ++k) {
            pd[i][k] = (accum[k] + pd[i][k]) % mod;
        }

        for (int k = 0; k < m && vec[i] != mx_num; ++k) {
            accum[k] = (accum[k] + pd[i][k]) % mod;
        }
    }

    vector<int> maxes;
    for (int i = 0; i < n; ++i) {
        if (vec[i] == mx_num) {
            maxes.push_back(i);
        }
    }

    int m1 = l_side.size() - 2;
    int m2 = r_side.size() - 2;

    ll ans = 0;
    for (size_t i = 0; i < maxes.size(); ++i) {
        for (size_t j = i; j < maxes.size(); ++j) {
            int x = maxes[i], y = maxes[j];
            int len = max(0ll, y - x - 1);

            int loc_ans = (dp[x][m1] * pd[y][m2]) % mod;
            loc_ans = (loc_ans * binpow(2, len)) % mod;

            ans = (ans + loc_ans) % mod;
        }
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
