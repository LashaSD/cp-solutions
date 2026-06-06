#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <cstdint>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2187B: Shortest Statement Ever
void solve()
{
    int x, y;
    cin >> x >> y;

    if ((x & y) == 0) {
        cout << x << ' ' << y << '\n';
        return;
    }

    int mask = 0;
    int ans = LLONG_MAX;
    int p = 0, q = 0;
    for (int i = 62; i >= 0; --i) {
        int bit = (1ll << i);
        mask |= bit;
        if (!(bit & x & y)) continue;
        pair<int, int> check_list[4];

        // decreasing y
        check_list[0] = {x & mask, y ^ bit | (bit - 1)};

        // decreasing x
        check_list[1] = {x ^ bit | (bit - 1), y & mask};

        // increasing y
        check_list[2] = {x, (y & mask) + bit};

        // increasing x
        check_list[3] = {(x & mask) + bit, y};

        for (int j = 0; j < 4; ++j) {
            auto [a, b] = check_list[j];
            if ((a & b) != 0) continue;
            if (abs(x - a) + abs(y - b) < ans) {
                ans = abs(x - a) + abs(y - b);
                p = a;
                q = b;
            }
        }
    }

    cout << p << ' ' << q << '\n';
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
