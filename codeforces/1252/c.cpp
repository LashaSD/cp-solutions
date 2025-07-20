#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

// 1252C: Even Path
void solve()
{
    int n, q;
    cin >> n >> q;
    vector<int> R(n), C(n);
    for (int& a: R) cin >> a;
    for (int& a: C) cin >> a;

    set<pair<pair<int, int>, bool>> row_parity;

    int l = 0, p = (R[0] % 2 == 0);
    for (int i = 1; i < n; ++i) {
        if (R[i] % 2 != R[i-1] % 2) {
            row_parity.insert({ {l, i-1}, (p == 1) });
            l = i;
            p = (R[i] % 2 == 0);
        }
    }
    row_parity.insert({ { l, n-1}, (p == 1) });

    set<pair<pair<int, int>, bool>> col_parity;

    l = 0, p = (C[0] % 2 == 0);
    for (int i = 1; i < n; ++i) {
        if (C[i] % 2 != C[i-1] % 2) {
            col_parity.insert({ {l, i-1}, (p == 1) });
            l = i;
            p = (C[i] % 2 == 0);
        }
    }
    col_parity.insert({ { l, n-1}, (p == 1) });

    auto fetch = [] (set<pair<pair<int, int>, bool>>& s, int x) {
        auto it = s.lower_bound({{x, x}, 1});
        if (it == s.end() || it->first.first > x) --it;
        return it;
    };

    for (int i = 0; i < q; ++i) {
        int r0, c0; cin >> r0 >> c0;
        int r1, c1; cin >> r1 >> c1;
        r0--, c0--;
        r1--, c1--;

        auto row_it = fetch(row_parity, r0);
        auto col_it = fetch(col_parity, c0);

        auto col_range = col_it->first;
        auto row_range = row_it->first;

        bool whole_col_ok = (col_range.first <= c0 && c0 <= col_range.second) && (col_range.first <= c1 && c1 <= col_range.second);
        bool whole_row_ok = (row_range.first <= r0 && r0 <= row_range.second) && (row_range.first <= r1 && r1 <= row_range.second);

        int row_l = row_it->first.first - 1, row_r = row_it->first.second - 1;

        bool ok = (whole_row_ok && whole_col_ok);
        cout << (ok ? "YES\n" : "NO\n");
    }
}

int T = 1;
int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // cin >> T;
    while(T--)
        solve();
    return 0;
}
