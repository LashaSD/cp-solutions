#include <climits>
#include <cstdio>
#include <algorithm>
#include <cstdint>
#include <queue>
#include <vector>
#include <queue>
#include <iostream>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

// B. Good Start
void solve()
{
    ll w, h, a, b;
    cin >> w >> h >> a >> b;
    ll x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    ll left_side_1 = x1;
    ll right_side_1 = x1 + a;

    ll left_side_2 = x2;
    ll right_side_2 = x2 + a;

    ll top_side_1 = y1 + b;
    ll bot_side_1 = y1;

    ll top_side_2 = y2 + b;
    ll bot_side_2 = y2;

    auto is_cross = [](ll l, ll r, ll l1, ll r1) -> bool {
        return (max(r1, r) - min(l, l1) + 1) < ((r1 - l1 + 1) + (r - l + 1) - 1);
    };

    ll y_diff = max(bot_side_2 - top_side_1, bot_side_1 - top_side_2);
    ll x_diff = max(left_side_2 - right_side_1, left_side_1 - right_side_2);

    // dbg(is_cross(2, 3, 3, 4));
    // dbg(x_diff, y_diff);

    // x cross
    if (is_cross(left_side_1, right_side_1, left_side_2, right_side_2)) {
        dbg("here");
        cout << ((y_diff % b) == 0 ? "Yes\n" : "No\n");
    } else if (is_cross(bot_side_1, top_side_1, bot_side_2, top_side_2)) {
        cout << ((x_diff % a) == 0 ? "Yes\n" : "No\n");
    } else {
        cout << (((x_diff % a) == 0 or (y_diff % b) == 0) ? "Yes\n" : "No\n");
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
