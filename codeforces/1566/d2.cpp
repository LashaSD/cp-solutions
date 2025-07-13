#include <algorithm>
#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

// 1566D2: Seating Arrangements (hard version)
void solve()
{
    int n, m;
    cin >> n >> m;
    map<int, int> used, f;
    vector<int> vec(n*m), s(n*m);
    vector<vector<int>> grid(n);

    for (int i = 0; i < n*m; ++i) {
        int num; cin >> num;
        f[num]++;
        vec[i] = s[i] = num;
    }

    sort(s.begin(), s.end());

    for (int i = 0; i < n; ++i) {
        for (int j = 1; j <= m; ++j) {
            grid[i].push_back(j);
        }
    }

    auto l = [&](int x) {
        return lower_bound(s.begin(), s.end(), x) - s.begin();
    };

    int ans = 0;
    reverse(vec.begin(), vec.end());
    for (int num: vec) {
        int cnt_lesser = l(num);

        // one based
        int min_pos = cnt_lesser + 1;
        int max_pos = min_pos + f[num] - 1 - used[num];
        used[num]++;

        // zero based
        int max_row = (max_pos - 1) / m;
        int min_row = (min_pos - 1) / m;

        // one based
        int min_col = min_row == max_row ? min_pos - (m*min_row) : 1;

        vector<int>& row_set = grid[max_row];

        int cost = 0;
        auto it = row_set.begin();
        while (it != row_set.end() && *it < min_col)
            cost++, it++;

        ans += cost;
        row_set.erase(it);
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
