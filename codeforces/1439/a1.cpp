#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

struct Entry {
    // first second third
    pair<int, int> f, s, t;
};

// 1439A1: Binary Table (Easy Version)
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<bool>> vec(n, vector<bool>(m));
    for (int i = 0; i < n; ++i) {
        string s; cin >> s;
        for (int j = 0; j < m; ++j) {
            char c = s[j];
            vec[i][j] = c == '1';
        }
    }

    vector<Entry> ans;

    // @param top left corner zero based
    function<void(int, int)> eval_square = [&](int x, int y) {
        vector<pair<int, int>> ones;
        if (vec[x][y] == 1) ones.push_back({x, y});
        if (vec[x+1][y] == 1) ones.push_back({x+1, y});
        if (vec[x][y+1] == 1) ones.push_back({x, y+1});
        if (vec[x+1][y+1] == 1) ones.push_back({x+1, y+1});

        int one_cnt = ones.size();
        Entry nxt = { {0, 0} };
        bool finished = true;
        if (one_cnt == 4) {
            nxt.f = {x, y+1}, nxt.s = {x+1, y+1}, nxt.t = {x+1, y};
            finished = false;
        } else if (one_cnt == 3) {
            nxt.f = ones[0], nxt.s = ones[1], nxt.t = ones[2];
        } else if (one_cnt == 2) {
            bool is_collumn = !(vec[x][y] ^ vec[x+1][y]);
            bool is_row = !(vec[x][y] ^ vec[x][y+1]);
            if (is_collumn) {
                // first collumn is fully on
                if (vec[x][y]) {
                    nxt.f = {x, y+1}, nxt.s = {x+1, y+1}, nxt.t = {x+1, y};
                } else {
                    nxt.f = {x, y}, nxt.s = {x+1, y}, nxt.t = {x+1, y+1};
                }
            } else if (is_row){
                if (vec[x][y]) {
                    nxt.f = {x, y}, nxt.s = {x+1, y}, nxt.t = {x+1, y+1};
                } else {
                    nxt.f = {x+1, y}, nxt.s = {x, y}, nxt.t = {x, y+1};
                }
            } else { // diagonal
                if (vec[x][y]) {
                    nxt.f = {x, y}, nxt.s = {x+1, y}, nxt.t = {x, y+1};
                } else {
                    nxt.f = {x, y+1}, nxt.s = {x, y}, nxt.t = {x+1, y+1};
                }
            }

            finished = false;
        } else if (one_cnt == 1) {
            pair<int, int> p = ones.front();
            // align the point to the left of the square
            p.second = y;

            nxt.f = p, nxt.s = { p.first, p.second + 1 }, nxt.t = { p.first + 1, p.second };

            // wrap around
            if (nxt.t.first > x+1) {
                nxt.t.first = x;
            }

            finished = false;
        } else if (one_cnt == 0) {
            return;
        }

        ans.push_back(nxt);
        vec[nxt.f.first][nxt.f.second] = !vec[nxt.f.first][nxt.f.second];
        vec[nxt.s.first][nxt.s.second] = !vec[nxt.s.first][nxt.s.second];
        vec[nxt.t.first][nxt.t.second] = !vec[nxt.t.first][nxt.t.second];

        if (not finished)
            eval_square(x, y);
    };

    for (int i = 0; i <= n-1; i+=2) {
        if (i == n-1)
            i--;

        for (int j = 0; j <= (m-1); j += 2) {
            if (j == m-1) {
                eval_square(i, j-1);
            } else {
                eval_square(i, j);
            }
        }
    }

    cout << ans.size() << '\n';
    for (Entry& e : ans) {
        cout << e.f.first + 1 << ' ' << e.f.second + 1 << ' ';
        cout << e.s.first + 1 << ' ' << e.s.second + 1 << ' ';
        cout << e.t.first + 1 << ' ' << e.t.second + 1 << '\n';
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
