#include <bits/stdc++.h>
#include <climits>
#include <iterator>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

// 1463C: Busy Robot
void solve()
{
    int n; cin >> n;
    vector<pair<ll, ll>> vec(n);
    for (auto& p: vec) {
        cin >> p.first >> p.second;
    }

    sort(begin(vec), end(vec));

    // moment -> {start pos, final pos}
    map<ll, pair<ll, ll>> from_to;
    set<pair<ll, ll>> moments;
    ll x = 0, t = 0;
    for (auto p: vec) {
        if (p.first < t) continue;
        t = p.first;
        ll dx = abs(p.second - x);
        from_to[t] = {x, p.second};
        moments.insert({t, t + dx});
        t += dx;
        x = p.second;
    }

    auto fetch = [&](ll t) {
        auto it = moments.upper_bound({t, LLONG_MAX});
        return *(--it);
    };

    dbg(moments);
    dbg(from_to);
    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        auto p = vec[i];
        ll T = p.first;
        ll X = p.second;

        auto t_range = fetch(T);
        auto t0 = t_range.first;
        auto t1 = i == n-1 ? t_range.second : min(vec[i+1].first, t_range.second);
        // auto t1 = min(vec[i+1].first, t_range.second);

        auto move = from_to[t0];
        ll x0 = move.first;
        ll sign = ((move.first > move.second) ? -1 : 1);

        if (T > t1) {
            ll final_pos = x0 + ((t1 - t0) * sign);
            dbg(t0, t1, T);
            dbg(x0, final_pos, X);
            cerr << '\n';
            if (X == final_pos) ans++;
            continue;
        }

        ll dt = T - t0;
        ll pos_at_t = x0 + ((T - t0) * sign);
        ll pos_at_end = x0 + ((t1 - t0) * sign);
        ll lower = min(pos_at_t, pos_at_end);
        ll upper = max(pos_at_t, pos_at_end);

        dbg(t0, t1);
        dbg(lower, upper, X);
        cerr << '\n';
        if (lower <= X && X <= upper) ans++;
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
