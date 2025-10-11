#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll

// 2052J: Judicious Watching
void solve()
{
    int n, m, q;
    cin >> n >> m >> q;
    vector<int> a(n), d(n), l(m), t(q);
    for (int& x: a)
        cin >> x;

    for (int& x: d)
        cin >> x;

    for (int& x: l)
        cin >> x;

    for (int& x: t)
        cin >> x;

    vector<pair<int, int>> vec(n);
    for (int i = 0; i < n; ++i) {
        vec[i].first = d[i];
        vec[i].second = a[i];
    }

    sort(vec.begin(), vec.end());

    vector<int> l_align(n+1);
    for (int i = 1; i <= n; ++i) {
        l_align[i] = l_align[i-1] + vec[i-1].second;
    }

    vector<int> r_align(n+1);
    r_align[n] = LLONG_MAX;
    for (int i = n-1; i >= 0; --i) {
        r_align[i] = min(vec[i].first, r_align[i+1]) - vec[i].second;
    }

    vector<int> ep_pref(m+1);
    for (int i = 1; i <= m; ++i) {
        ep_pref[i] = ep_pref[i-1] + l[i-1];
    }

    sort(d.begin(), d.end());

    vector<int> ans(q);
    for (int i = 0; i < q; ++i) {
        int ti = t[i];
        int r_idx = upper_bound(d.begin(), d.end(), ti) - d.begin();
        int right_most = min(ti, r_align[r_idx]);

        int left_most = l_align[r_idx];

        int len = right_most - left_most;
        auto it = upper_bound(ep_pref.begin(), ep_pref.end(), len) - 1;

        //cerr << "DBG: " << left_most << ' ' << right_most << ' ' << r_idx << '\n';
        //if (it != ep_pref.end()) {
        //    cerr << "EP: " << *it << '\n';
        //}

        ans[i] = max(0ll, (it - ep_pref.begin()));
    }

    for (int x: ans)
        cout << x << ' ';
    cout << '\n';
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
