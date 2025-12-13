
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define xx first
#define yy second

// 2126G1: Big Wins! (easy version)
void solve()
{
    int n; cin >> n;
    vector<int> a(n+1);
    int m = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        m = max(m, a[i]);
    }

    vector<vector<int>> pm(m+1, vector<int>(n+1));
    for (int x = 1; x <= m; ++x) {
        for (int i = 1; i <= n; ++i) {
            pm[x][i] = pm[x][i-1] + (a[i] >= x ? 1 : -1);
        }
    }

    vector<vector<int>> pmin(m+1, vector<int>(n+1));
    vector<vector<int>> smax(m+1, vector<int>(n+1));
    for (int x = 1; x <= m; ++x) {
        for (int i = 1; i <= n; ++i) {
            pmin[x][i] = min(pmin[x][i-1], pm[x][i]);
        }
    }

    for (int x = 1; x <= m; ++x) {
        smax[x][n] = pm[x][n];
        for (int i = n-1; i >= 1; --i) {
            smax[x][i] = max(smax[x][i+1], pm[x][i]);
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        for (int x = m; x >= 1; --x) {
            if (smax[x][i] - pmin[x][i-1] >= 0) {
                //cerr << "DBG: " << i << ' ' << x << '\n';
                //cerr << "DBG: " << pmin[x][i-1] << ' ' << smax[x][i] << '\n' << '\n';
                ans = max(ans, x - a[i]);
                break;
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
