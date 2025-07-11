#include <algorithm>
#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

// 1795C: Tea Tasting
void solve()
{
    int n; cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }

    vector<ll> pref_b(n, 0), dead_count(n, 0), leftover(n, 0);
    pref_b[0] = b[0];
    for (int i = 1; i < n; ++i)
        pref_b[i] = pref_b[i-1] + b[i];

    dbg(pref_b);
    for (int i = 0; i < n; ++i) {
        ll sum = i != 0 ? pref_b[i-1] : 0;
        ll num = a[i] + sum;
        auto it = lower_bound(pref_b.begin() + i, pref_b.end(), num);
        if (it != pref_b.end()) {
            int idx = it - pref_b.begin();
            ll remaining = a[i];
            if (it != pref_b.begin()) {
                remaining = num - *(it-1);
            }

            dead_count[idx]++;
            dbg(num, remaining, idx);
            leftover[idx] += remaining;
        }
        sum += b[i];
    }

    for (int i = 1; i < n; ++i) {
        dead_count[i] += dead_count[i-1];
    }

    for (int i = 0; i < n; ++i) {
        int num = b[i];
        ll ans = num * ((i+1) - dead_count[i]) + leftover[i];
        cout << ans << ' ';
    }
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
