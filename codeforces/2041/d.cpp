#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

const int inf = 1e18;

using P = pair<int, int>;
vector<P> offsets = {
    {-1, 0},
    {0, 1},
    {1, 0},
    {0, -1},
};

// 2041D: Drunken Maze
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<vector<vector<int>>>> dp(n, vector<vector<vector<int>>>(m, vector<vector<int>>(4, vector<int>(4, inf))));
    vector<vector<char>> grid(n, vector<char>(m));
    P src, dest;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> grid[i][j];
            if (grid[i][j] == 'S') {
                src = {i, j};
            } else if (grid[i][j] == 'T') {
                dest = {i, j};
            }
        }
    }

    queue<array<int, 4>> q;
    dp[src.xx][src.yy][0][0] = 0;
    q.push({src.xx, src.yy, 0, 0});
    while (q.size() > 0) {
        auto [i, j, d, s] = q.front();
        int dist = dp[i][j][d][s];
        q.pop();
        for (int dir = 0; dir < 4; ++dir) {
            auto [di, dj] = offsets[dir];
            if (grid[i + di][j + dj] == '#') continue;
            if (d == dir && s + 1 > 3) continue;
            int ns = d == dir ? s + 1 : 1;
            if (dp[i + di][j + dj][dir][ns] != inf) continue;
            dp[i + di][j + dj][dir][ns] = dist + 1;
            q.push({i + di, j + dj, dir, ns});
        }
    }

    int ans = inf;
    for (int d = 0; d < 4; ++d) {
        for (int s = 0; s < 4; ++s) {
            ans = min(ans, dp[dest.xx][dest.yy][d][s]);
        }
    }

    cout << (ans == inf ? -1 : ans) << '\n';
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
