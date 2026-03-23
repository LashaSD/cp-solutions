#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

const vector<pair<int, int>> offsets = {
    {0, -1},
    {-1, -1},
    {-1, 0},
    {-1, 1},
    {0, 1},
    {1, 1},
    {1, 0},
    {1, -1},
};

// AOC2025: Printing Department
// day 4 part 1
signed main()
{
    vector<string> grid;
    while (cin >> grid.emplace_back());
    grid.pop_back();

    int n = grid.size();
    int m = grid.front().size();
    cerr << "SIZE: " << n << ' ' << m << '\n';
    int ans = 0;
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if (grid[r][c] != '@') continue;

            int cnt = 0;
            for (auto [dr, dc]: offsets) {
                int r1 = r + dr;
                int c1 = c + dc;
                if (r1 < 0 || r1 >= n || c1 < 0 || c1 >= m) continue;
                if (grid[r1][c1] == '@')
                    cnt++;
            }

            if (cnt < 4) ans++;
        }
    }

    cout << ans << '\n';
}
