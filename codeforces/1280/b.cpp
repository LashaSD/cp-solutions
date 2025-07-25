#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<bool>> grid(n, vector<bool>(m));
    int freaky = 0;
    for (int i = 0; i < n; ++i) {
        string s; cin >> s;
        for (int j = 0; j < m; ++j) {
            grid[i][j] = (s[j] == 'A');
            if (grid[i][j]) freaky++;
        }
    }

    if (freaky == 0) {
        cout << "MORTAL\n";
        return;
    }

    int corner_row = 0, corner_col = 0;
    int corner_cnt = 0;
    for (int i = 0; i < n; ++i) {
        corner_cnt += grid[i][0];
    }

    if (corner_cnt == n) corner_col = 1;

    corner_cnt = 0;
    for (int i = 0; i < n; ++i) {
        corner_cnt += grid[i][m-1];
    }

    if (corner_cnt == n) corner_col = 1;

    corner_cnt = 0;
    for (int j = 0; j < m; ++j) {
        corner_cnt += grid[0][j];
    }

    if (corner_cnt == m) corner_row = 1;

    corner_cnt = 0;
    for (int j = 0; j < m; ++j) {
        corner_cnt += grid[n-1][j];
    }

    if (corner_cnt == m) corner_row = 1;

    int full_rows = 0, full_columns = 0;
    for (int i = 0; i < n; ++i) {
        int cnt = 0;
        for (int j = 0; j < m; ++j) {
            if (grid[i][j]) cnt++;
        }
        if (cnt == m) full_rows++;
    }

    for (int j = 0; j < m; ++j) {
        int cnt = 0;
        for (int i = 0; i < n; ++i) {
            if (grid[i][j]) cnt++;
        }
        if (cnt == n) full_columns++;
    }

    bool center_outer = 0;
    bool corner_outer = grid[0][0] || grid[0][m-1] || grid[n-1][0] || grid[n-1][m-1];
    for (int i = 0; i < n; ++i) {
        if (grid[i][0] || grid[i][m-1]) center_outer = 1;
    }

    for (int j = 0; j < m; ++j) {
        if (grid[0][j] || grid[n-1][j]) center_outer = 1;
    }

    if (full_rows == n) {
        cout << 0 << '\n';
    } else if (corner_row || corner_col) {
        cout << 1 << '\n';
    } else if (corner_outer || full_rows > 0 || full_columns > 0) {
        cout << 2 << '\n';
    } else if (center_outer) {
        cout << 3 << '\n';
    } else {
        cout << 4 << '\n';
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
