#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll

// GYM106144E: Limousine Rally
void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<char>> grid(n+1, vector<char>(m+1));
    for (int i = 1; i <= n; ++i) {
        string s; cin >> s;
        for (int j = 1; j <= m; ++j) {
            grid[i][j] = s[j-1];
        }
    }

    vector<vector<int>> pref(n+1, vector<int>(m+1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            pref[i][j] = pref[i-1][j] + (grid[i][j] == 'x');
        }
    }

    auto good = [&](int r, int c) {
        if (r + k - 1 > n || r < 1 || c > m || c < 1) {
            return false;
        }

        return (pref[r+k-1][c] - pref[r-1][c]) == 0;
    };

    vector<vector<bool>> visited(n+1, vector<bool>(m+1));
    queue<pair<int, int>> q;
    q.push({1, 1});
    while (!q.empty()) {
        auto [r, c] = q.front();
        visited[r][c] = 1;
        q.pop();

        if (good(r+1, c)) {
            if (!visited[r+1][c]) {
                visited[r+1][c] = 1;
                q.push({r+1, c});
            }
        }

        if (good(r, c-1)) {
            if (!visited[r][c-1]) {
                visited[r][c-1] = 1;
                q.push({r, c-1});
            }
        }

        if (good(r, c+1)) {
            if (!visited[r][c+1]) {
                visited[r][c+1] = 1;
                q.push({r, c+1});
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (visited[i][j]) {
                ans = max(ans, i + k - 1);
            }
        }
    }

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
