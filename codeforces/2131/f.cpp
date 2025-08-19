#include <algorithm>
#include <bits/stdc++.h>
#include <climits>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

// 2131F: Unjust Binary Life
void solve()
{
    int n; cin >> n;
    string a, b;
    cin >> a >> b;

    vector<ll> pa_ones(n+1), pa_zeroes(n+1);
    for (int i = 0; i < n; ++i) {
        pa_ones[i+1] = pa_ones[i] + (a[i] == '1');
        pa_zeroes[i+1] = pa_zeroes[i] + (a[i] == '0');
    }

    vector<ll> p1(n+1), p0(n+1);
    for (int i = 0; i < n; ++i) {
        p1[i+1] = p1[i] + (b[i] == '1');
        p0[i+1] = p0[i] + (b[i] == '0');
    }

    using plpll = pair<ll, pair<ll, ll>>;

    // delta = cnt(1) - cnt(0)
    vector<plpll> diffs(n);
    for (int i = 1; i <= n; ++i) {
        diffs[i-1] = {p1[i] - p0[i], {p1[i], p0[i]}};
    }

    sort(diffs.begin(), diffs.end());

    for (int i = n-2; i >= 0; --i) {
        diffs[i].second.second += diffs[i+1].second.second;
    }

    for (int i = 1; i < n; ++i) {
        diffs[i].second.first += diffs[i-1].second.first;
    }

    #ifndef ONLINE_JUDGE
    for (int i = 0; i < n; ++i) {
        cerr << diffs[i].first << ' ' << diffs[i].second.first << ' ' << diffs[i].second.second << '\n';
    }
    cerr << '\n';
    #endif

    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        ll c_ones = pa_ones[i+1];
        ll c_zeroes = pa_zeroes[i+1];
        ll delta = c_ones - c_zeroes;

        auto breakpoint = lower_bound(diffs.begin(), diffs.end(), (plpll){ -delta, {LLONG_MIN, LLONG_MIN} });

        int cnt_front = breakpoint - diffs.begin();
        int cnt_back = diffs.end() - breakpoint;

        ll ones = 0;
        ll zeroes = 0;

        dbg(*breakpoint);
        dbg(cnt_front, cnt_back);
        if (breakpoint == diffs.end()) {
            ones = (--breakpoint)->second.first + (c_ones * cnt_front);
        } else if (breakpoint->first > -delta && breakpoint == diffs.begin()) {
            zeroes = breakpoint->second.second + (c_zeroes * cnt_back);
        } else {
            zeroes = breakpoint->second.second + (c_zeroes * cnt_back);
            if (breakpoint != diffs.begin()) {
                ones = (--breakpoint)->second.first + (c_ones * cnt_front);
            }
        }

        ans += ones + zeroes;

        dbg(delta, ones, zeroes);
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
