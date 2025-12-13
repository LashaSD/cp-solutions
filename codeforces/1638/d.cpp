#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

static const vector<pair<int, int>> offsets = {
    {0, 0},
    {0, 1},
    {1, 0},
    {1, 1},
};

static const vector<pair<int, int>> sq_offsets = {
    // horizontal
    {0, -1},
    {0, 1},

    // up
    {-1, -1},
    {-1, 0},
    {-1, 1},

    // down
    {1, -1},
    {1, 0},
    {1, 1},
};

// 1638D: Big Brush
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> grid(n+1, vector<int>(m+1));
    vector<vector<bool>> mark(n+1, vector<bool>(m+1));
    vector<vector<bool>> in_q(n+1, vector<bool>(m+1));
    vector<vector<int>> col(n+1, vector<int>(m+1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> grid[i][j];
        }
    }

    vector<pair<int, int>> q;
    for (int i = 1; i <= n-1; ++i) {
        for (int j = 1; j <= m-1; ++j) {
            int c = grid[i][j];
            bool ok = 1;
            for (auto [di, dj]: offsets) {
                if (grid[i+di][j+dj] != c)
                    ok = 0;
            }

            if (ok) {
                col[i][j] = c;
                q.push_back({i, j});
                in_q[i][j] = 1;
            }
        }
    }

    auto push_neighbors = [&](int i, int j) {
        for (auto [di, dj]: sq_offsets) {
            int i1 = i + di, j1 = j + dj;
            if (in_q[i1][j1]) continue;

            int c = 0;
            for (auto [ddi, ddj]: offsets) {
                int i2 = i1 + ddi, j2 = j1 + ddj;
                if (i2 < 1 || i2 > n ||
                    j2 < 1 || j2 > m)
                {
                    c = 0;
                    break;
                }

                if (mark[i2][j2]) continue;
                if (c == 0) {
                    c = grid[i2][j2];
                    continue;
                }

                if (grid[i2][j2] != c) {
                    c = 0;
                    break;
                }
            }

            if (c > 0) {
                col[i1][j1] = c;
                q.push_back({i1, j1});
                in_q[i1][j1] = 1;
            }
        }
    };

    vector<pair<int, pair<int, int>>> ans;
    while (!q.empty()) {
        auto [i, j] = q.back();
        q.pop_back();

        ans.push_back({col[i][j], {i, j}});
        
        for (auto [di, dj]: offsets) {
            mark[i+di][j+dj] = 1;
        }

        push_neighbors(i, j);
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (!mark[i][j]) {
                cout << -1 << '\n';
                return;
            }
        }
    }

    reverse(ans.begin(), ans.end());
    cout << ans.size() << '\n';
    for (auto [c, p]: ans) {
        cout << p.xx << ' ' << p.yy << ' ' << c << '\n';
    }
}

int T = 1;
int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //cin >> T;
    while(T--)
        solve();

    return 0;
}
