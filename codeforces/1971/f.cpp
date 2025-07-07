#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

// 1971F: Circle Perimeter
void solve()
{
    int r; cin >> r;
    const int LOWER = r*r;
    const int UPPER = (r + 1)*(r + 1);
    auto ok = [&](int x, int y) {
        ll res = x*x + y*y;
        return (res >= LOWER) && (res < UPPER);
    };

    if (r == 1) {
        cout << 8 << '\n';
        return;
    } else if (r == 2) {
        cout << 16 << '\n';
        return;
    }

    bool corner_count = false;
    function<int(int, int)> dfs = [&](int x, int y) {
        if (x > r || y > r || y < x) return 0;
        if (x == y && ok(x, y)) {
            corner_count = true;
            return 0;
        }

        if (ok(x, y)) {
            dbg(x, y);
            int ans = 1;
            ans += dfs(x+1, y);
            ans += dfs(x, y-1);
            if (ans == 1) {
                ans += dfs(x+1, y-1);
            }
            return ans;
        }

        return 0;
    };

    int count = dfs(1, r);
    dbg(count);

    // int count = 0;
    // for (int x = 1, y = r; y > x && x <= r; x++) {
    //     bool o = ok(x, y);
    //     if (o)
    //         count++;
    //     else {
    //         x-=1, y--;
    //         dbg((x+1), y);
    //         if ((x+1) == y)
    //             corner_count = true;
    //     }
    // }

    int ans = 4 + count * 8 + corner_count * 4;

    dbg(count, corner_count);
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
