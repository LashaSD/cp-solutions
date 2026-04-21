#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2113C: Smilo and Minecraft
void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<string> grid(n);
    int goldcnt = 0;
    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
        for (char c: grid[i]) {
            if (c == 'g')
                goldcnt++;
        }
    }

    // gpref[i] = prefix sum of gold counts of row i
    vector<vector<int>> gpref(n, vector<int>(m+1, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j <= m; ++j) {
            gpref[i][j] = gpref[i][j-1] + (grid[i][j-1] == 'g');
        }
    }

    // returns how much gold is inside k size square centered at (r, c)
    auto rect = [&](int r, int c) {
        ll cnt = 0;

        int tl = c-k+1, tr = c+k-1;
        // one based
        tl++, tr++;
        if (tr > m) tr = m;
        if (tl < 1) tl = 1;

        for (int i = r-k+1; i <= r+k-1; ++i) {
            if (0 <= i && i <= n-1) {
                cnt += gpref[i][tr] - gpref[i][tl-1];
            }
        }

        return cnt;
    };

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == '.') {
                int cnt = rect(i, j);
                ans = max(ans, goldcnt - cnt);
                cerr.flush();
            }
        }
    }

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
