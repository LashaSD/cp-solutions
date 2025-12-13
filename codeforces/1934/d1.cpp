#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 1934D1: XOR Break — Solo Version
void solve()
{
    int n, m;
    cin >> n >> m;
    int B = 63 - __builtin_clzll(n);
    int i = B, j = B;
    for (; i >= 0; --i) {
        int b = (1ll << i);
        if (n & b) break;
    }

    for (j = i - 1; j >= 0; --j) {
        int b = (1ll << j);
        if (n & b) break;
    }

    if (j < 0) {
        cout << -1 << '\n';
        return;
    }

    for (int k = i - 1; k > j; --k) {
        int b = (1ll << k);
        if (m & b) {
            cout << -1 << '\n';
            return;
        }
    }

    int mi = (m & (1ll << i));
    int mj = (m & (1ll << j));
    bool special = mi == 0 && mj == 0;

    if (mi != 0 && mj != 0)
    for (int k = j-1; k >= 0; --k) {
        int b = (1ll << k);
        bool nb = (n & b) != 0;
        bool mb = (m & b) != 0;
        if (nb && !mb) {
            break;
        } else if (!nb && mb) {
            cout << -1 << '\n';
            return;
        }
    }

    if (special) {
        cout << 2 << '\n' << n << ' ' << (m | (1ll << B)) << ' ' << m << '\n';
    } else {
        cout << 1 << '\n' << n << ' ' << m << '\n';
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
