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

#define int ll

const int maxN = 205, maxM = 205;
int n, m;
char grid[maxN][maxM];
bool mark[maxN][maxM];

bool simulate(int r, int c, char state)
{
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            mark[i][j] = 0;
        }
    }

    while (r < n && r >= 0 && c < m && c >= 0) {
        mark[r][c] = 1;

        if (grid[r][c] == '/') {
            if (state == 'U') state = 'R';
            else if (state == 'D') state = 'L';
            else if (state == 'R') state = 'U';
            else if (state == 'L') state = 'D';
        } else if (grid[r][c] == '\\') {
            if (state == 'U') state = 'L';
            else if (state == 'D') state = 'R';
            else if (state == 'R') state = 'D';
            else if (state == 'L') state = 'U';
        }

        if (state == 'R') {
            c++;
        } else if (state == 'L') {
            c--;
        } else if (state == 'U') {
            r--;
        } else if (state == 'D') {
            r++;
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] != '.' && !mark[i][j]) {
                return false;
            }
        }
    }

    return true;
}

// 2045M: Mirror Maze
void solve()
{
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> grid[i][j];
        }
    }

    vector<pair<char, int>> ans;
    for (int i = 0; i < n; ++i) {
        if (simulate(i, 0, 'R')) {
            ans.push_back({'W', i + 1});
        }

        if (simulate(i, m-1, 'L')) {
            ans.push_back({'E', i + 1});
        }
    }

    for (int i = 0; i < m; ++i) {
        if (simulate(0, i, 'D')) {
            ans.push_back({'N', i + 1});
        }

        if (simulate(n-1, i, 'U')) {
            ans.push_back({'S', i + 1});
        }
    }

    cout << ans.size() << '\n';
    for (auto [s, i]: ans) {
        cout << s << i << ' ';
    }
    cout << '\n';
}

int T = 1;
int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // cin >> T;
    while(T--)
        solve();

    return 0;
}
