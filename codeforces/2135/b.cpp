#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second
using P = pair<int, int>;

// 2135B: For the Champion
void solve()
{
    int k = 1e9;
    int n; cin >> n;
    const int INF = 1e9 + 10000;
    int x1 = INF, y1 = INF, x2 = INF, y2 = INF;
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        if (x1 == INF) {
            x1 = x;
            y1 = y;
        } else {
            // top left {-k, +k}
            int d1 = abs(x + k) + abs(y - k);
            int d2 = abs(x1 + k) + abs(y1 - k);
            if (d1 < d2) {
                x1 = x;
                y1 = y;
            }
        }

        if (x2 == INF) {
            x2 = x;
            y2 = y;
        } else {
            // top right {+k, +k}
            int d1 = abs(x - k) + abs(y - k);
            int d2 = abs(x2 - k) + abs(y2 - k);
            if (d1 < d2) {
                x2 = x;
                y2 = y;
            }
        }
    }

    int c1, c2;
    (cout << "? L " << k << '\n').flush();
    cin >> c1;

    (cout << "? U " << k << '\n').flush();
    cin >> c1;

    (cout << "? L " << k << '\n').flush();
    cin >> c1;

    (cout << "? U " << k << '\n').flush();
    cin >> c1;

    (cout << "? R " << k << '\n').flush();
    cin >> c2;

    (cout << "? R " << k << '\n').flush();
    cin >> c2;

    (cout << "? R " << k << '\n').flush();
    cin >> c2;

    (cout << "? R " << k << '\n').flush();
    cin >> c2;

    int y = (c1 + c2 - x1 + x2 + y1 + y2 - 8*k) / 2;
    int x = c2 + x2 + y2 - 4*k - y;
    (cout << "! " << x << ' ' << y << '\n').flush();
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
