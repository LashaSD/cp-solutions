#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

int rv(int x) {
    int res = 0;
    int msb = 63 - __builtin_clzll(x);
    for (int i = 0; i <= msb; ++i) {
        int b = (1ll << i);
        if (b & x) {
            res |= (1ll << (msb - i));
        }
    }

    return res;
}

int tr(int x) {
    while ((x & 1) == 0) {
        x >>= 1;
    }
    return x;
}

bool is_pow(int x) {
    for (int i = 0; i < 63; ++i) {
        int b = (1ll << i);
        if (x == b-1) return 1;
    }

    return 0;
}

bool check(int x, int y)
{
    int k = 63 - __builtin_clzll(x);
    int msb = 63 - __builtin_clzll(y);
    for (int i = 0; i + k <= msb; ++i) {
        int c = y >> i;
        int mask = (1ll << (k+1)) - 1;
        if (x == (c & mask)) {
            bool ok = 1;
            // check if rest is all ones
            if (i > 0) {
                int lo_mask = (1ll << i) - 1;
                ok &= (lo_mask & y) == ((1ll << i) - 1);
            }

            int hi_mask = (1ll << (msb - (i + k) + 1)) - 1;
            int d = (y >> (i + k)) | 1;
            ok &= is_pow(tr(d & hi_mask));

            if (ok) {
                return 1;
            } 
        }
    }

    return 0;
}

// 1618F: Reverse
void solve()
{
    //cout << check(0b1011, 0b111011) << '\n';
    int x, y;
    cin >> x >> y;
    if (x == y) {
        cout << "YES\n";
        return;
    }

    int p1 = __builtin_popcountll(x);
    int p2 = __builtin_popcountll(y);
    if (p1 > p2) {
        cout << "NO\n";
        return;
    }

    if (p2 == 1) {
        cout << (rv(x) == y || tr(x) == y ? "YES\n" : "NO\n");
        return;
    }

    bool ok = check(tr(x), y);
    ok |= check(rv(tr(x)), y);
    ok |= check((x << 1) | 1, y);
    ok |= check(rv((x << 1) | 1), y);
    cout << (ok ? "YES\n" : "NO\n");
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
