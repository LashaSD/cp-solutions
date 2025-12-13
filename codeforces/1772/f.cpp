#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

int n, m, k;
const int maxN = 35;
const int maxK = 105;
int grid[maxK][maxN][maxN];

const vector<pair<int, int>> offsets = {
    {0, -1},
    {-1, 0},
    {0, 1},
    {1, 0},
};

// 1772F: Copy of a Copy of a Copy
void solve()
{
    cin >> n >> m >> k;
    k++;
    for (int kk = 0; kk < k; ++kk) {
        for (int i = 0; i < n; ++i) {
            string s; cin >> s;
            for (int j = 0; j < m; ++j) {
                grid[kk][i][j] = s[j] == '1';
            }
        }
    }

    vector<int> d(k);
    for (int kk = 0; kk < k; ++kk) {
        for (int i = 1; i < n-1; ++i) {
            for (int j = 1; j < m-1; ++j) {
                int x = grid[kk][i][j];
                bool b = 1;
                for (auto [di, dj]: offsets) {
                    if (grid[kk][i + di][j + dj] != 1 - x) {
                        b = 0;
                        break;
                    }
                }

                if (b) d[kk]++;
            }
        }
    }

    vector<int> order(k);
    for (int i = 0; i < k; ++i)
        order[i] = i;

    sort(order.begin(), order.end(), [&](int u, int v) {
        return d[u] > d[v];
    });

    vector<pair<int, int>> buf;
    buf.reserve(n*m);

    vector<array<int, 3>> ans;
    for (int kk = 0; kk < k-1; ++kk) {
        int k1 = order[kk];
        int k2 = order[kk+1];

        buf.clear();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[k1][i][j] != grid[k2][i][j]) {
                    buf.push_back({i, j});
                }
            }
        }

        for (auto [i, j]: buf) {
            ans.emplace_back();
            ans.back()[0] = 1;
            ans.back()[1] = i+1;
            ans.back()[2] = j+1;
        }

        ans.emplace_back();
        ans.back()[0] = 2;
        ans.back()[1] = k2+1;
    }

    cout << order[0] + 1 << '\n';
    cout << ans.size() << '\n';
    for (int i = 0; i < (int) ans.size(); ++i) {
        cout << ans[i][0] << ' ';
        if (ans[i][0] == 1) {
            cout << ans[i][1] << ' ' << ans[i][2] << '\n';
        } else {
            cout << ans[i][1] << '\n';
        }
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
