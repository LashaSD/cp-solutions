#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

// 1579C: Ticks
void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<bool>> grid(n, vector<bool>(m));
    vector<vector<int>> len(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        string s; cin >> s;
        int j = 0;
        for (char c: s) {
            grid[i][j] = c == '*';
            ++j;
        }
    }

    auto process = [&](int i, int j) {
        pair<int, int> l = {i-1, j-1}, r = {i-1, j+1};
        int h = 0;
        while (l.first >= 0 && l.second >= 0 && r.second <= (m-1)) {
            if (!grid[l.first][l.second] || !grid[r.first][r.second])
                break;

            h++;
            l.first--, r.first--;
            l.second--, r.second++;
        }

        len[i][j] = max(len[i][j], h);
        l = {i-1, j-1}, r = {i-1, j+1};
        int h_it = 1;
        while (h_it++ <= h) {
            len[l.first][l.second] = max(len[l.first][l.second], h);
            len[r.first][r.second] = max(len[r.first][r.second], h);
            l.first--, r.first--;
            l.second--, r.second++;
        }
    };

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j])
                process(i, j);
        }
    }

    int ans = INT_MAX;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j]) {
                ans = min(ans, len[i][j]);
            }
        }
    }

    cout << (ans >= k ? "YES\n" : "NO\n");
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
