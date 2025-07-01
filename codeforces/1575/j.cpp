#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

const int DOWN = 2;
const int RIGHT = 1;
const int LEFT = 3;

const int MAXN = 1e6 + 4;

int p[MAXN+1];

// J. Jeopardy of Dropped Balls
void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> vec(n, vector<int>(m));
    auto idx = [m](int row, int col) -> int {
        return row * m + col;
    };

    auto rev_idx = [m](int node) -> pair<int, int> {
        return { node / m, node % m };
    };

    function<int(int)> find_set = [&](int u) {
        if (p[u] == u) return u;
        return p[u] = find_set(p[u]);
    };

    function<void(int, int)> join = [&](int u, int v) {
        int head_u = find_set(u);
        int head_v = find_set(v);
        p[head_u] = head_v;
    };

    for (int i = 0; i < (n*m); ++i) {
        p[i] = i;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int t; cin >> t;
            vec[i][j] = t;
            if (t == DOWN && i > 0 && vec[i-1][j] == DOWN) {
                join(idx(i-1, j), idx(i, j));
            }
        }
    }

    for (int it = 0; it < k; ++it) {
        int row = 0, col = 0;
        cin >> col; col--;
        int last_row = row, last_col = col;

        while (row < n) {
            if (vec[row][col] == DOWN) {
                int node = find_set(idx(row, col));
                pair<int, int> next_node = rev_idx(node);
                last_row = row;
                last_col = col;
                row = next_node.first+1;
                col = next_node.second;
                continue;
            }

            if (last_row < row && last_col == col) {
                join(idx(last_row, last_col), idx(row, col));
            }

            if (row + 1 < n && vec[row+1][col] == DOWN) {
                join(idx(row, col), idx(row+1, col));
            }

            last_col = col;
            if (vec[row][col] == RIGHT) {
                col++;
            } else {
                col--;
            }

            vec[row][last_col] = DOWN;
        }
        dbg(row, col);
        cout << (col+1) << ' ';
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
