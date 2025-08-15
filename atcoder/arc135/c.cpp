#include <bits/stdc++.h>
#include <climits>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

// ARC135C: XOR to All
void solve()
{
    static const int BIT_CNT = 63;

    int n; cin >> n;
    vector<ll> vec(n);
    vector<ll> sum(BIT_CNT);
    // vector<ll> carry(BIT_CNT);

    for (int i = 0; i < n; ++i) {
        cin >> vec[i];
    }

    for (int i = 0; i < n; ++i) {
        ll x = vec[i];
        for (int pos = 0; pos < BIT_CNT; ++pos) {
            ll bit = (1ll << pos);
            if ((x & bit) != 0) {
                sum[pos]++;
            }
        }
    }

    auto val = [](vector<ll>& p_sum) -> ll {
        ll result = 0;

        for (int pos = 0; pos < BIT_CNT; ++pos) {
            ll bit = (1ll << pos);
            result += (bit * p_sum[pos]);
        }

        return result;
    };

    sort(vec.begin(), vec.end(), greater<ll>());

    vector<ll> loc_sum = sum;
    ll accum = 0;
    for (int i = 0; i < n; ++i) {
        ll x = vec[i] ^ accum;

        // compute sum table when x is xored

        loc_sum = sum;
        for (int pos = 0; pos <= BIT_CNT; ++pos) {
            ll bit = (1ll << pos);
            ll bit_is_on = (x & bit) != 0;
            if (bit_is_on) {
                loc_sum[pos] = n - sum[pos];
            }
        }

        if (val(loc_sum) > val(sum)) {
            dbg(i, x);
            accum ^= x;
            sum = loc_sum;
        }
    }

    cout << val(sum) << '\n';
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
