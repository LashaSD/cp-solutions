#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// 1904D1: Set To Max (Easy Version)
void solve()
{
    int n; cin >> n;
    vector<int> a(n), b(n);
    for (int& x: a)
        cin >> x;

    for (int& x: b)
        cin >> x;

    vector<bool> blocked(n);

    auto run_r = [&](int l, int r, int mx) {
        int loc_mx = 0;
        for (int i = l; i < n; ++i) {
            loc_mx = max(loc_mx, a[i]);
            if (blocked[i]) break;

            if (loc_mx == mx && i >= r) {
                return i;
            }
        }

        return -1;
    };

    auto run_l = [&](int l, int r, int mx) {
        int loc_mx = 0;
        for (int i = r; i >= 0; --i) {
            loc_mx = max(loc_mx, a[i]);

            if (blocked[i]) break;

            if (loc_mx == mx && i <= l) {
                return i;
            }
        }

        return -1;
    };

    vector<pair<int, pair<int, int>>> ranges;
    int l = 0, r = -1;
    for (int i = 0; i < n; ++i) {
        if (i == n-1 || b[i] != b[i+1]) {
            r = i;
            ranges.push_back({b[i], {l, r}});
            l = i+1;       
        }
    }

    sort(ranges.begin(), ranges.end());

    for (int i = 0; i < (int) ranges.size(); ++i) {
        auto p = ranges[i];
        int x = p.first;
        int l = p.second.first;
        int r = p.second.second;

        int tr = run_r(l, r, x);
        int tl = run_l(l, r, x);

        for (int j = l; j <= r; ++j) {
            blocked[j] = 1;
        }

        if (tl != -1) {
            l = tl;
        } else if (tr != -1) {
            r = tr;
        } else {
            break;
        }

        for (int j = l; j <= r; ++j) {
            a[j] = x;
        }
    }

    for (int i = 0; i < n; ++i) {
        if (a[i] != b[i]) {
            cout << "NO\n";
            return;
        }
    }

    cout << "YES\n";
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
