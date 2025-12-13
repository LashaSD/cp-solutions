#include <iostream>
#include <cassert>
#include <climits>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <map>

using namespace std;
using ll = long long;

#define int ll

// 1721D: Maximum AND
void solve()
{
    int n; cin >> n;
    vector<int> a(n), b(n);
    int mx = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        mx = max(mx, a[i]);
    }

    for (int i = 0; i < n; ++i) {
        cin >> b[i];
        mx = max(mx, b[i]);
    }

    int max_k = 63 - __builtin_clzll(mx);
    int ans = 0;
    for (int k = max_k; k >= 0; k--) {
        int bit = (1ll << k);
        sort(a.begin(), a.end());
        sort(b.begin(), b.end(), greater<int>());

        bool ok = false;
        for (int i = 0; i < n; ++i) {
            int x = a[i] & bit;
            int y = b[i] & bit;

            if ((x && !y) || (!x && y)) {
                ok = true;
            } else {
                ok = false;
                break;
            }
        }

        if (!ok) {
            for (int i = 0; i < n; ++i) {
                if ((a[i] & bit)) a[i] ^= bit;
                if ((b[i] & bit)) b[i] ^= bit;
            }
        } else {
            ans |= bit;
        }
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
