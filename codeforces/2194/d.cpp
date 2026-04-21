#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2194D: Table Cut
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> vec(n, vector<int>(m));
    int ones = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> vec[i][j];
            if (vec[i][j] == 1)
                ones++;
        }
    }

    vector<vector<bool>> used(n, vector<bool>(m));

    int target = ones / 2;
    queue<pair<int, int>> q;
    q.push({n-1, 0});
    int current = 0;
    while (q.size() > 0) {
        pair<int, int> top = q.front();
        q.pop();
        auto [r, c] = top;
        if (used[r][c]) continue;

        used[r][c] = 1;
        if (vec[r][c] == 1) {
            // cerr << r << ' ' << c << '\n';
            current++;
        }

        if (current == target) {
            break;
        }

        if (r > 0) {
            q.push({r - 1, c});
        }

        if (c < m-1) {
            q.push({r, c+1});
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            // cerr << used[i][j] << ' ';
        }
        // cerr << '\n';
    }

    int r = 0, c = 0;
    string ans;
    while (r != n || c != m) {
        if (r == n) {
            c++;
            ans.push_back('R');
        } else if (c == m) {
            r++;
            ans.push_back('D');
        } else {
            if (!used[r][c]) {
                r++;
                ans.push_back('D');
            } else {
                c++;
                ans.push_back('R');
            }
        }
    }

    int ideal = ones % 2 == 0 ? (ones/2)*(ones/2) : (ones/2) * ((ones+1)/2);
    cout << ideal << '\n';
    cout << ans << '\n';
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
