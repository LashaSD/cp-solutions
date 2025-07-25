#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

// (((( ) (((( ))) (( )))

// 1556C: Compressed Bracket Sequence
void solve()
{
    int n; cin >> n;
    n /= 2;
    vector<pair<int, int>> vec(n);

    for (auto& i: vec)
        cin >> i.first >> i.second;

    unsigned long long ans = 0;
    for (int i = 0; i < n; ++i) {
        // left brace
        int opened = vec[i].first;
        // right brace
        int closed = vec[i].second;
        ans += min(opened, closed);

        ll leftover_closed = max(0, closed - min(opened, closed));
        ll strict_closed = 0;

        if (opened > closed) continue;

        for (int j = i-1; j >= 0; --j) {
            auto last = vec[j];
            ll lopened = last.first;
            ll lclosed = last.second;

            if (strict_closed > 0) {
                ll temp = lopened;
                lopened = max(0ll, lopened - strict_closed);
                strict_closed = max(0ll, strict_closed - temp);
            }

            if (lclosed + strict_closed > lopened) {
                strict_closed += (lclosed - min(lclosed, lopened));
                continue;
            }

            ll pairs = min(lopened, lclosed);
            ans++;

            if (lopened > lclosed) {
                ll diff = lopened - lclosed;
                ans += min(diff, leftover_closed);
                leftover_closed -= diff;

                if (leftover_closed < 0) break;
            }
        }
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
