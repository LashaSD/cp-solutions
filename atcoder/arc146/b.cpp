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

// ARC146B: Plus and AND
void solve()
{
    ull n, m, k;
    cin >> n >> m >> k;
    vector<ull> vec(n);
    for (ull& i: vec)
        cin >> i;

    ull BIT_CNT = 0;
    ull mx = *max_element(vec.begin(), vec.end()) + m;
    for (int pos = 63; pos >= 0; --pos) {
        if ((mx & (1ull << pos)) != 0) {
            BIT_CNT = pos;
            break;
        }
    }

    auto min_ops = [&](ull x, ull mask) {
        if ((x & mask) == mask) {
            return 0ull;
        }

        int l = BIT_CNT;
        while (l >= 0) {
            ull bit = (1ull << l);
            bool x_on = (bit & x) != 0;
            bool mask_on = (bit & mask) != 0;
            if (!x_on && mask_on) break;
            l--;
       }

        ull segment = (1ull << l) - 1;
        ull sum = (((x >> l) << l) | mask) | (segment & mask);

        return sum - x;
    };

    vector<ull> cost(n);
    auto ok = [&](ull mid) {
        for (int i = 0; i < n; ++i) {
            ull x = vec[i];
            ull loc_cost = min_ops(x, mid);
            cost[i] = loc_cost;
        }

        sort(cost.begin(), cost.end());

        ull sum = 0;
        for (int i = 0; i < k; ++i) {
            sum += cost[i];
        }

        return sum <= m;
    };

    ull mask = 0;
    for (int pos = BIT_CNT; pos >= 0; pos--) {
        ull bit = (1ull << pos);
        ull loc_mask = mask | bit;
        if (ok(loc_mask)) {
            mask = loc_mask;
        }
    }

    cout << mask << '\n';
}

int T = 1;
int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // cin >> T;
    while(T--)
        solve();
}
