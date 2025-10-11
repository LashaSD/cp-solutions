#include <iostream>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;
using ll = long long;

#define int ll

// 2152D: Division Versus Addition
void solve()
{
    int n, q; 
    cin >> n >> q;
    vector<int> vec(n);
    for (int i = 0; i < n; ++i) 
        cin >> vec[i];

    vector<int> pref(n+1);
    vector<int> cnt(n+1);
    for (int i = 1; i <= n; ++i) {
        int x = vec[i-1];
        int y = 63 - __builtin_clzll(x);
        int z = cnt[i-1];

        if (x == (1ll << y) + 1) {
            pref[i] = pref[i-1] + y;
            cnt[i] = cnt[i-1] + 1;
        } else {
            if (x != (1ll << y)) y++;

            pref[i] = pref[i-1] + y;
            cnt[i] = cnt[i - 1];
        }
    }

    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        l--, r--;

        int ans = pref[r+1] - pref[l] + ((cnt[r+1] - cnt[l]) / 2);
        cout << ans << '\n';
    }
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
