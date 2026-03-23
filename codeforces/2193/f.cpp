#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

using pii = pair<int, int>;

static inline int man(const pii& a, const pii& b)
{
    return abs(b.xx - a.xx) + abs(b.yy - a.yy);
}

// 2193F: Pizza Delivery
void solve()
{
    int n;
    pii A, B;
    cin >> n;
    cin >> A.xx >> A.yy;
    cin >> B.xx >> B.yy;

    vector<pii> points(n);
    for (int i = 0; i < n; ++i) {
        cin >> points[i].xx;
    }

    for (int i = 0; i < n; ++i) {
        cin >> points[i].yy;
    }

    // {{bot, top}}
    vector<array<pii, 2>> vec;
    sort(points.begin(), points.end());
    for (int i = 0; i < n; ++i) {
        auto [x, y] = points[i];
        if (vec.empty() || vec.back()[0].xx != x) {
            vec.emplace_back();
            vec.back()[0] = {x, y};
            vec.back()[1] = {x, y};
        }

        vec.back()[0].yy = min(vec.back()[0].yy, y);
        vec.back()[1].yy = max(vec.back()[1].yy, y);
    }

    int m = vec.size();

    // if flag -> go to b first then a
    // if !flag -> go to a first then b
    auto compute = [](int a, int b, int m, bool flag) {
        return flag ? abs(b - m) + abs(b - a) : abs(m - a) + abs(b - a);
    };

    // [i][j] = min moves
    // i = i-th point
    // j = 1 -> top most
    // j = 0 -> bottom most
    vector<vector<int>> dp(m, vector<int>(2, LLONG_MAX));

    dp[0][0] = (vec[0][0].xx - A.xx) + compute(vec[0][0].yy, vec[0][1].yy, A.yy, true);
    dp[0][1] = (vec[0][0].xx - A.xx) + compute(vec[0][0].yy, vec[0][1].yy, A.yy, false);
    for (int i = 1; i < m; ++i) {
        for (int j2 = 0; j2 < 2; ++j2) {
            for (int j1 = 0; j1 < 2; ++j1) {
                int dx = (vec[i][j1].xx - vec[i-1][j2].xx);
                dp[i][j1] = min(dp[i-1][j2] + dx + compute(vec[i][0].yy, vec[i][1].yy, vec[i-1][j2].yy, j1 == 0), dp[i][j1]);
            }
        }
    }

    cout << min(dp[m-1][0] + man(vec[m-1][0], B), dp[m-1][1] + man(vec[m-1][1], B)) << '\n';
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
