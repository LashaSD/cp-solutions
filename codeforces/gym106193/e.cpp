#include <bits/stdc++.h>
#include <numbers>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

static const vector<pair<int, int>> offsets = {
    {0, -1},
    {-1, -1},
    {-1, 0},
    {-1, 1},
    {0, 1},
    {1, 1},
    {1, 0},
    {1, -1},
};

char query(int r, int c)
{
    cout << "? " << r << ' ' << c << '\n';
    cout.flush();
    char c1; cin >> c1;
    return c1;
}

int n;

// ICPC,GYM106193E: Eight-Connected Figures
void solve()
{
    set<pair<int, int>> q, blacks, whites, visited;
    auto proc = [&](int r, int c, bool blk) {
        visited.insert({r, c});

        if (blk) {
            blacks.insert({r, c});
        } else {
            whites.insert({r, c});
        }

        vector<pair<int, int>> wb;
        for (auto [dr, dc]: offsets) {
            if (visited.find({r + dr, c + dc}) != visited.end()) {
                continue;
            }

            bool black = 0, white = 0;
            for (auto [ddr, ddc]: offsets) {
                int r1 = r + dr + ddr, c1 = c + dc + ddc;

                if (blacks.find({r1, c1}) != blacks.end()) {
                    black = 1;
                } else if (whites.find({r1, c1}) != whites.end()) {
                    white = 1;
                }
            }

            if (black && white) {
                wb.push_back({r + dr, c + dc});
            }
        }

        if (wb.size() > 0) {
            q.insert(wb.begin(), wb.end());
        }
    };

    pair<int, int> last_pt = {0, 1};
    while (true) {
        if (q.size() > 0) {
            int r = q.begin()->first, c = q.begin()->second;
            q.erase(q.begin());
            char c1 = query(r, c);
            proc(r, c, c1 == 'B');
            last_pt = {r, c};
        } else {
            auto [r0, c0] = last_pt;
            int r, c;
            for (auto [dr, dc]: offsets) {
                if (visited.find({r0 + dr, c0 + dc}) == visited.end()) {
                    r = r0 + dr, c = c0 + dc;
                    break;
                }
            }

            if (blacks.find({r0, c0}) != blacks.end()) {
                whites.clear();
            } else {
                blacks.clear();
            }

            char c1 = query(r, c);
            proc(r, c, c1 == 'B');
            last_pt = {r, c};
        }

        if ((int) whites.size() >= n) {
            cout << "! W ";
            for (auto [r1, c1]: whites) {
                cout << r1 << ' ' << c1 << ' ';
            }
            cout << '\n';
            cout.flush();
            return;
        } else if ((int) blacks.size() >= n) {
            cout << "! B ";
            for (auto [r1, c1]: blacks) {
                cout << r1 << ' ' << c1 << ' ';
            }
            cout << '\n';
            cout.flush();
            return;
        }
    }
}

int T = 1;
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    cin >> n;
    while(T--)
        solve();

    return 0;
}
