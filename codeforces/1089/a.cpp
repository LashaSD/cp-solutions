#include <iostream>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <map>

using namespace std;
using ll = long long;

#define int ll

pair<bool, vector<pair<int, int>>> dp[4][4][208][208];

void precompute()
{
    dp[0][0][0][0].first = true;
    for (int s = 0; s <= 3; ++s) {
        for (int t = 0; t <= 3; ++t) {
            if (t == 3 && s == 3) continue;
            if (t == 0 && s == 0) continue;

            for (int a = 0; a <= 200; ++a) {
                for (int b = 0; b <= 200; ++b) {
                    int threshold = 25;
                    if (s + t == 5) threshold = 15;

                    for (int x = threshold, y = 0; x <= a && y <= b && t != 3 && s > 0; ++y, x += (x - y < 2)) {
                        bool ok = dp[s-1][t][a-x][b-y].first;
                        vector<pair<int, int>>& last = dp[s-1][t][a-x][b-y].second;
                        vector<pair<int, int>>& current = dp[s][t][a][b].second;
                        if (ok) {
                            dp[s][t][a][b].first = true;
                            current = last;
                            current.push_back(make_pair(x, y));
                            break;
                        }
                    }

                    for (int x = 0, y = threshold; x <= a && y <= b && s != 3 && t > 0; ++x, y += (y - x < 2)) {
                        bool ok = dp[s][t-1][a-x][b-y].first;
                        vector<pair<int, int>>& last = dp[s][t-1][a-x][b-y].second;
                        vector<pair<int, int>>& current = dp[s][t][a][b].second;
                        if (ok) {
                            dp[s][t][a][b].first = true;
                            current = last;
                            current.push_back(make_pair(x, y));
                            break;
                        }
                    }
                }
            }
        }
    }
}

vector<pair<int, int>> priorities = {
    {3, 0},
    {3, 1},
    {3, 2},
    {2, 3},
    {1, 3},
    {0, 3}
};

// 1089A: Alice the Fan
void solve()
{
    int a, b;
    cin >> a >> b;
    for (auto [s, t]: priorities) {
        if (dp[s][t][a][b].first) {
            cout << s << ":" << t << '\n';
            for (auto p: dp[s][t][a][b].second) {
                cout << p.first << ':' << p.second << ' ';
            }
            cout << '\n';
            return;
        }
    }

    cout << "Impossible\n";
}

int T = 1;
int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    precompute();

    cin >> T;
    while(T--)
        solve();
    return 0;
}
