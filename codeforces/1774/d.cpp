#include <cstdio>
#include <algorithm>
#include <cstdint>
#include <vector>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

// D. Same Count One
void solve()
{
    int n, m;
    scanf("%d %d", &n, &m);
    vector<vector<bool>> vec(n, vector<bool>(m, 0));
    vector<int> oneCnt(n);

    int ones = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int temp;
            scanf("%d", &temp);

            if (temp == 1) {
                ones++;
                oneCnt[i]++;
            }

            vec[i][j] = (bool) temp;
        }
    }

    if (ones % n != 0) {
        printf("-1\n");
        return;
    }

    int portion = ones / n;

    vector<pair<pair<int, int>, int>> ans;
    auto swp = [&](int i, int j, int pos) {
        swap(vec[i][pos], vec[j][pos]);
        ans.push_back({{i+1, j+1}, pos+1});
        oneCnt[i]--;
        oneCnt[j]++;
    };

    for (int col = 0; col < m; ++col) {
        vector<int> overQ, underQ;
        for (int row = 0; row < n; ++row) {
            if (oneCnt[row] > portion and vec[row][col]) {
                overQ.push_back(row);
            }

            if (oneCnt[row] < portion and not vec[row][col]) {
                underQ.push_back(row);
            }
        }

        for (int idx = 0; idx < overQ.size() and idx < underQ.size(); ++idx) {
            int overPt = overQ[idx];
            int underPt = underQ[idx];
            swp(overPt, underPt, col);
        }
    }

    printf("%d\n", (int) ans.size());
    for (auto& s : ans) {
        printf("%d %d %d\n", s.first.first, s.first.second, s.second);
    }
}

int T = 1;
int32_t main(void)
{
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    scanf("%d", &T);
    while(T--)
        solve();
    return 0;
}
