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

int n, m, k;
vector<pair<int, string>> moves;

vector<string> round_move = {
    "RDL",
    "R",
    "RD",
};

void go_down_round()
{
    int d = min(3*(n - 1), k);
    if (d / 3 > 0)
        moves.push_back({d / 3, "RDL"});

    int r = d % 3;
    if (r > 0) {
        moves.push_back({1, round_move[r]});
    }

    k -= d;
}

static inline void go_left()
{
    int d = min(m-1, k);
    if (d > 0)
        moves.push_back({d, "L"});

    k -= d;
}

static inline void go_right_one()
{
    int d = min(1ll, k);
    if (d > 0)
        moves.push_back({1, "R"});
    k -= d;
}

static inline void go_up()
{
    int d = min(n - 1, k);
    if (d > 0)
        moves.push_back({d, "U"});
    k -= d;
}

static inline void go_down()
{
    int d = min(n - 1, k);
    if (d > 0)
        moves.push_back({d, "D"});
    k -= d;
}

// 1301D: Time to Run
void solve()
{
    cin >> n >> m >> k;

    go_down();
    go_up();
    for (int i = 0; i < m-1; ++i) {
        go_down_round();
        go_right_one();
        go_up();
    }
    go_left();

    if (k > 0) {
        cout << "NO\n";
        return;
    }

    cout << "YES\n";
    cout << moves.size() << '\n';
    for (int i = 0; i < (int) moves.size(); ++i) {
        cout << moves[i].first << ' ' << moves[i].second << '\n';
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
