#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 1903D1: Maximum And Queries (easy version)
void solve()
{
    int n, q;
    cin >> n >> q;
    vector<int> vec(n);
    for (int i = 0; i < n; ++i) {
        cin >> vec[i];
    }

    for (int qi = 0; qi < q; ++qi) {
        int k; cin >> k;
        int mask = 0;
        int ans = 0;
        vector<int> v = vec;
        for (int bi = 62; bi >= 0; --bi) {
            int bit = (1ll << bi);
            mask |= bit;
            int cost = 0;
            for (int x: v) {
                if (x & bit) {
                    continue;
                }

                cost += ((x | bit) & mask) - x;
                if (cost > k) break;
            }

            if (cost <= k) {
                ans |= bit;
                for (int i = 0; i < n; ++i) {
                    if (!(v[i] & bit)) {
                        v[i] = (v[i] | bit) & mask;
                    }
                }
                k -= cost;
            }
        }

        cout << ans << '\n';
    }
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
