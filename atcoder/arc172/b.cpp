#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

const int MOD = 998244353;

// ARC172B: AtCoder Language
void solve()
{
    ll n, k, l;
    cin >> n >> k >> l;
    ll ans = 1ll;
    int break_point = n - k + 1;
    ll track = l;
    ll fixed = l - (break_point - 1);
    for (int i = 0; i < n; ++i) {
        if (i >= break_point) {
            ans = ((ans % MOD) * (fixed % MOD)) % MOD;
            continue;
        }

        ans = ((ans % MOD) * (track % MOD)) % MOD;
        track = max(0ll, track - 1);
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
