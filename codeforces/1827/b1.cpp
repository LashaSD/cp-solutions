#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define xx first
#define yy second

const int inf = 2e9;

// 1827B1: Range Sorting (Easy Version)
void solve()
{
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<vector<int>> dp(n, vector<int>(n, -1));
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            if (a[i] > a[j]) {
                dp[i][j] = i;
            }
        }
    }

    for (int j = 0; j < n; ++j) {
        for (int i = n-2; i >= 0; --i) {
            if (dp[i][j] == -1)
                dp[i][j] = dp[i+1][j];
        }
    }

    ll ans = 0;
    vector<pair<int, int>> segs;
    for (int i = 0; i < n; ++i) {
        int j = i+1;
        ll sum = 0;
        segs.clear();
        for (; j < n; ++j) {
            int l = dp[i][j];
            if (l == -1) {
                ans += sum;
                continue;
            }

            while (segs.size() > 0) {
                auto [l1, r1] = segs.back();
                if (l1 > l) {
                    sum -= r1 - l1;
                    segs.pop_back();
                } else {
                    l = max(r1, l);
                    break;
                }
            }

            sum += (ll) (j - l);
            segs.push_back({l, j});
            ans += sum;
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
