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
using pii = pair<int, int>;

#define xx first
#define yy second

#define int ll

// 1185E: Polycarp and Snakes
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<string> grid(n);
    pii zero = {0, 0};
    vector<pair<pii, pii>> line(26, make_pair(zero, zero));
    char mx = 'a' - 1;
    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char c = grid[i][j];
            if (c == '.') continue;

            mx = max(mx, c);

            if (line[c - 'a'].xx == zero) {
                line[c - 'a'].xx = make_pair(i + 1, j + 1);
            } else {
                auto [r0, c0] = line[c - 'a'].xx;
                auto [r1, c1] = line[c - 'a'].yy;

                if ((i + 1) != r0 && (j + 1) != c0) {
                    cout << "NO\n";
                    return;
                }

                if (r1 != 0 && c1 != 0) 
                if ((r0 == r1 && (i + 1) != r0) ||
                    (c0 == c1 && (j + 1) != c0))
                {
                    cout << "NO\n";
                    return;
                }

                line[c - 'a'].yy = make_pair(i + 1, j + 1);
            }
        }
    }

    for (int k = 0; k < 26; ++k) {
        if (line[k].xx == zero || line[k].yy == zero) continue;

        auto [r0, c0] = line[k].xx;
        auto [r1, c1] = line[k].yy;

        for (int i = r0-1; i < r1; i++) {
            if (grid[i][c0 - 1] == '.') {
                cout << "NO\n";
                return;
            }
        }

        for (int j = c0-1; j < c1; j++) {
            if (grid[r0 - 1][j] == '.') {
                cout << "NO\n";
                return;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == '.') continue;

            for (int k = grid[i][j] - 'a' + 1; k < 26; ++k) {
                auto [r0, c0] = line[k].xx;
                auto [r1, c1] = line[k].yy;
                if (r0 <= (i + 1) && (i + 1) <= r1 &&
                    c0 <= (j + 1) && (j + 1) <= c1) 
                {
                    cout << "NO\n";
                    return;
                }
            }
        }
    }

    for (char m = mx; m >= 'a'; m--) {
        int i = m - 'a';
        if (line[i].xx != zero && line[i].yy == zero) {
            line[i].yy = line[i].xx;
        } else if (line[i].xx == zero && line[i].yy == zero) {
            line[i] = line[i+1];
        }
    }

    cout << "YES\n";
    cout << mx - 'a' + 1 << '\n';
    for (int i = 0; i <= mx - 'a'; ++i) {
        auto [r0, c0] = line[i].xx;
        auto [r1, c1] = line[i].yy;
        cout << r0 << ' ' << c0 << ' ' << r1 << ' ' << c1 << '\n';
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
