#include <algorithm>
#include <bits/stdc++.h>
#include <iomanip>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

struct Point {
    int x, y;
};

// C. Ela and Crickets
void solve()
{
    int n; cin >> n;
    Point a, b, c, t;
    cin >> a.x >> a.y;
    cin >> b.x >> b.y;
    cin >> c.x >> c.y;
    cin >> t.x >> t.y;

    Point top_left = { .x = min(a.x, min(b.x, c.x)), .y = max(a.y, max(b.y, c.y))};
    Point bot_right = { .x = max(a.x, max(b.x, c.x)), .y = min(a.y, min(b.y, c.y))};

    int corner_x = top_left.x < t.x ? bot_right.x : top_left.x;
    int corner_y = top_left.y <= t.y ? top_left.y : bot_right.y;

    Point center = {
        .x = (a.x == b.x) ? a.x : c.x,
        .y = (a.y == b.y) ? a.y : c.y,
    };

    int block_idx_x = (abs(corner_x - t.x) + 1) / 2;
    int to_left = corner_x > t.x ? 1 : -1;

    int block_idx_y = (abs(corner_y - t.y) + 1) / 2;
    int to_bottom = corner_y > t.y ? 1 : -1;

    Point t_top_left = {
        .x = top_left.x - (block_idx_x * 2 * to_left),
        .y = top_left.y - (block_idx_y * 2 * to_bottom),
    };

    vector<Point> table = {
        {.x = a.x - top_left.x, .y = a.y - top_left.y},
        {.x = b.x - top_left.x, .y = b.y - top_left.y},
        {.x = c.x - top_left.x, .y = c.y - top_left.y},
    };

    dbg(top_left.x, top_left.y);
    dbg(t_top_left.x, t_top_left.y);

    if ((center.x == 1 && center.y == 1) || (center.x == n && center.y == n) || (center.x == 1 && center.y == n) || (center.x == n && center.y == 1)) {
        if (t.x == center.x || t.y == center.y) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
        return;
    }

    for (Point p : table) {
        Point current = {
            .x = t_top_left.x + p.x,
            .y = t_top_left.y + p.y,
        };

        dbg(current.x, current.y);
        if (current.x == t.x && current.y == t.y) {
            cout << "YES\n";
            return;
        }
    }

    cout << "NO\n";
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

