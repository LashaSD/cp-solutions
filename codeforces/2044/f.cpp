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

const int maxN = 2e5 + 5;

// 2044F: Easy Demon Problem
void solve()
{
    int n, m, q;
    cin >> n >> m >> q;
    vector<int> a(n), b(m);

    ll sa = 0, sb = 0;

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        sa += a[i];
    }

    for (int i = 0; i < m; ++i) {
        cin >> b[i];
        sb += b[i];
    }

    vector<bool> ma(2 * maxN), mb(2 * maxN);
    for (int i = 0; i < n; ++i) {
        int val = sa - a[i];
        if (abs(val) <= maxN) {
            ma[maxN + val] = 1;
        }
    }

    for (int i = 0; i < m; ++i) {
        int val = sb - b[i];
        if (abs(val) <= maxN) {
            mb[maxN + val] = 1;
        }
    }

    auto ok = [&](int a, int b) {
        return (ma[maxN + a] && mb[maxN + b]) || (ma[maxN + b] && mb[maxN + a]);
    };

    for (int i = 0; i < q; ++i) {
        int x; cin >> x;
        bool neg = x < 0;
        x = abs(x);
        bool f = false;
        for (int j = 1; j*j <= x; ++j) {
            if (x % j != 0) continue;
            if (neg) {
                if (ok(-j, x/j) || ok(j, -x/j)) {
                    f = true;
                    break;
                }
            } else {
                if (ok(-j, -x/j) || ok(j, x/j)) {
                    f = true;
                    break;
                }
            }
        }

        cout << (f ? "YES\n" : "NO\n");
    }
}

int T = 1;
int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //cin >> T;
    while(T--)
        solve();

    return 0;
}
