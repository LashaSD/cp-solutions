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

void comp_pref(vector<vector<int>>& dest, vector<vector<int>>& source)
{
    int n = dest.size() - 1;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            dest[i][j] = (dest[i-1][j] + dest[i][j-1] - dest[i-1][j-1]) + source[i][j];
        }
    }
}

static inline int get_val(vector<vector<int>>& src, int r, int c, int r1, int c1)
{
    return src[r1][c1] - src[r - 1][c1] - src[r1][c - 1] + src[r-1][c-1];
}

// 2044H: Hard Demon Problem
void solve()
{
    int n, q;
    cin >> n >> q;

    vector<vector<int>> grid(n + 1, vector<int>(n + 1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> grid[i][j];
        }
    }

    // mult prefix grid && fixed prefix grid
    vector<vector<int>> m_pgrid(n + 1, vector<int>(n + 1)), f_pgrid(n + 1, vector<int>(n + 1));
    for (int i = 1; i <= n; ++i) {
        int m = i;

        for (int j = 1; j <= n; ++j) {
            f_pgrid[i][j] = m * grid[i][j];
        }

        for (int j = 1; j <= n; ++j) {
            m_pgrid[i][j] = m * grid[i][j];
            m++;
        }
    }

    vector<vector<int>> pgrid = grid;

    comp_pref(pgrid, grid);
    comp_pref(m_pgrid, m_pgrid);
    comp_pref(f_pgrid, f_pgrid);

    for (int qq = 0; qq < q; ++qq) {
        int r, c;
        int r1, c1;
        cin >> r >> c;
        cin >> r1 >> c1;

        int ans = get_val(m_pgrid, r, c, r1, c1);
        //cerr << "DBG0: " << ans << '\n';

        int v1 = get_val(pgrid, r, c, r1, c1); 
        //cerr << "DBG2: " << v1 << '\n';
        ans -= v1 * (r - 1 + c - 1);

        if (r1 > r && c1 > c) {
            int v = get_val(f_pgrid, r+1, c, r1, c1) - (get_val(pgrid, r+1, c, r1, c1) * r);
            //cerr << "DBG1: " << v << '\n';
            ans += v * (c1 - c);
        }

        cout << ans << ' ';
    }
    cout << '\n';
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
