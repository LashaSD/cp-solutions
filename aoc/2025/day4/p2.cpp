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
// day 4 part 2
signed main()
{
    vector<string> grid;
    while (cin >> grid.emplace_back());
    grid.pop_back();
    int n = grid.size();
    int m = grid.front().size();

    queue<pair<int, int>> q;
    vector<vector<bool>> inQ(n, vector<bool>(m));

    auto score = [&](int r, int c) {
        int cnt = 0;
        for (auto [dr, dc]: offsets) {
            int r1 = r + dr;
            int c1 = c + dc;
            if (r1 < 0 || r1 >= n || c1 < 0 || c1 >= m) continue;
            if (grid[r1][c1] == '@')
                cnt++;
        }

        return cnt;
    };

    auto update_neighbors = [&](int r, int c) {
        for (auto [dr, dc]: offsets) {
            int r1 = r + dr;
            int c1 = c + dc;
            if (r1 < 0 || r1 >= n || c1 < 0 || c1 >= m) continue;
            if (grid[r1][c1] == '@' && !inQ[r1][c1] && score(r1, c1) < 4) {
                inQ[r1][c1] = 1;
                q.push(make_pair(r1, c1));
            }
        }
    };

    int ans = 0;
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if (grid[r][c] != '@') continue;
            int cnt = score(r, c);
            if (cnt < 4) q.push(make_pair(r, c));
            while (q.size() > 0) {
                auto [i, j] = q.front();
                q.pop();
                grid[i][j] = 'X';
                ans++;
                update_neighbors(i, j);
            }
        }
    }

    cout << ans << '\n';
}
