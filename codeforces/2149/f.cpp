#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <cstdint>
#include <set>
#include <cstdio>
#include <algorithm>
#include <functional>
#include <map>

#define assert(v) do { if (!(v)) { __builtin_trap(); } } while (0)

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2149F: Nezuko in the Clearing
void solve()
{
    int h, d;
    cin >> h >> d;

    int l = 0, r = d;
    int save = -1;
    while (l <= r) {
        int b = l + (r - l) / 2;
        int k = d / (b+1);
        int m = d % (b+1);
        bool ok = 2*(h+b) > m*(k+1)*(k+2) + (b+1-m)*k*(k+1);
        if (ok) {
            save = b;
            r = b-1;
        } else {
            l = b+1;
        }
    }

    assert(save >= 0);
    cout << d + save << '\n';
}

int T = 1;
int32_t main(void)
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    cin >> T;
    while(T--)
        solve();

    return 0;
}
