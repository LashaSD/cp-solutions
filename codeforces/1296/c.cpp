#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

const int MAX_N = 2e5 + 5;

ll translate(int x0, int y0)
{
    ll x = MAX_N + x0;
    ll y = MAX_N + y0;
    return ((y - 1) * MAX_N) + x;
}

// 1296C: Yet Another Walking Robot
void solve()
{
    int n; cin >> n;
    string s; cin >> s;
    // translate(x, y) -> index in s
    map<ll, int> pos;

    int x = 0, y = 0;
    pair<int, int> seg = {0, INT_MAX};
    for (int i = 0; i < n; ++i) {
        char c = s[i];
        if (c == 'L')
            x--;
        else if (c == 'R')
            x++;
        else if (c == 'U')
            y++;
        else if (c == 'D')
            y--;

        // one based
        int index = pos[translate(x, y)];
        if (index != 0 || (x == 0 && y == 0)) {
            // segment found
            if (x == 0 && y == 0 && index == 0) index = 0;

            int mx_seg_len = seg.second - seg.first + 1;
            int curr_seg_len = i - index + 1;
            if (curr_seg_len < mx_seg_len) {
                seg.first = index;
                seg.second = i;
            }
        }

        pos[translate(x, y)] = i+1;
    }

    if (seg.second == INT_MAX) cout << -1 << '\n';
    else cout << seg.first + 1 << ' ' << seg.second + 1 << '\n';
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
