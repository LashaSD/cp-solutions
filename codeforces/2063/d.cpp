#include <iostream>
#include <cassert>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <deque>

using namespace std;
using ll = long long;

#define int ll

// 2063D: Game With Triangles
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (int i = 0; i < n; ++i)
        cin >> a[i];

    for (int i = 0; i < m; ++i)
        cin >> b[i];

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    int k_max = 0;
    int l = 0, r = 0;
    while (l <= n && r <= m) {
        int len_a = n - l;
        int len_b = m - r;
        if (len_a > len_b) {
            if (l + 2 > n || r + 1 > m) break;
            l += 2;
            r += 1;
        } else {
            if (l + 1 > n || r + 2 > m) break;
            l += 1;
            r += 2;
        }

        k_max++;
    }

    vector<int> pref_a(n+1), pref_b(m+1);
    for (int i = 1; i <= n; ++i) {
        pref_a[i] = pref_a[i-1] + a[i-1];
    }

    for (int i = 1; i <= m; ++i) {
        pref_b[i] = pref_b[i-1] + b[i-1];
    }

    auto f = [&](int i, int j) {
        return (pref_a[n] - pref_a[n - i]) - pref_a[i] + 
               (pref_b[m] - pref_b[m - j]) - pref_b[j];
    };

    vector<int> ans(k_max + 1);
    for (int k = 1; k <= k_max; ++k) {
        int l = max(0ll, 2*k - m), r = min(k, n - k);
        while (l < r) {
            int m1 = l + (r - l) / 3;
            int m2 = r - (r - l) / 3;
            int f1 = f(m1, k - m1);
            int f2 = f(m2, k - m2);
            if (f1 < f2) {
                l = m1 + 1;
            } else {
                r = m2 - 1;
            }
        }
        ans[k] = f(l, k - l);
    }

    cout << k_max << '\n';
    for (int k = 1; k <= k_max; ++k)
        cout << ans[k] << ' ';
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
