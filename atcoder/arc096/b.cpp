#include <algorithm>
#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;
using ull = unsigned long long;

const int MAX_N = 1e5 + 5;

// ARC096B: Static Sushi
void solve()
{
    int n; cin >> n;
    ll c; cin >> c;
    using pll = pair<ll, ll>;
    vector<pll> vec(n);
    for (pll& x: vec)
        cin >> x.first >> x.second;

    sort(vec.begin(), vec.end());

    // clockwise
    vector<ll> pref(n + 1);
    for (int i = 0; i < n; ++i) {
        pref[i+1] = pref[i] + vec[i].second;
    }

    vector<ll> running_mx_pref(n+1, 0);
    for (int i = 1; i <= n; ++i) {
        running_mx_pref[i] = max(running_mx_pref[i-1], (pref[i] - vec[i-1].first));
    }

    // counter clockwise
    vector<ll> suff(n+1, 0);
    for (int i = 0; i < n; ++i) {
        suff[i+1] = suff[i] + vec[n-i-1].second;
    }

    vector<ll> running_mx_suff(n+1, 0);
    for (int i = 1; i <= n; ++i) {
        running_mx_suff[i] = max(running_mx_suff[i-1], suff[i] - (c - vec[n-i].first));
    }

    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        ll x = pref[i+1] - vec[i].first;
        ll counter_mx = running_mx_suff[n-i-1] - vec[i].first;
        if (counter_mx > 0) x += counter_mx;

        ll y = suff[i+1] - (c - vec[n-i-1].first);
        ll clockwise_mx = running_mx_pref[n-i-1] - (c - vec[n-i-1].first);
        if (clockwise_mx > 0) y += clockwise_mx;

        ans = max(ans, max(x, y));
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
