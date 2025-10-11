#include <iostream>
#include <cstdint>
#include <vector>

using namespace std;
using ll = long long;

#define int ll

// 2051F: Joker
void solve()
{
    int n, m, q;
    cin >> n >> m >> q;

    vector<pair<int, int>> ranges(3, {0, 0});

    if (m == 1) ranges[0] = {1, 1};
    else if (m == n) ranges[2] = {n, n};
    else ranges[1] = {m, m};

    vector<int> a(q);
    for (int i = 0; i < q; ++i) {
        int x; cin >> x;

        bool add_ranges = 0;
        for (auto& r: ranges) {
            if (r.first == 0 || r.second == 0) continue;

            if (r.first <= x && x <= r.second) {
                add_ranges = 1;
                if (r.first == r.second) {
                    r.first = 0;
                    r.second = 0;
                }
            } else if (x < r.first) {
                r.first = max(1ll, r.first - 1);
            } else if (x > r.second) {
                r.second = min(n, r.second + 1);
            }
        }

        if (add_ranges) {
            if (ranges[0].first == 0) {
                ranges[0].first = 1;
                ranges[0].second = 1;
            }

            if (ranges[2].first == 0) {
                ranges[2].first = n;
                ranges[2].second = n;
            }
        }

        int l = 0;
        int ans = 0;
        for (auto r: ranges) {
            if (r.first == 0 || r.second == 0) continue;

            l = max(l, r.first);
            ans += max(0ll, r.second - l + 1);
            l = r.second + 1;
            //cerr << "DBG: " << r.first << ' ' << r.second << '\n';
        }
        cerr << '\n';

        a[i] = ans;
    }

    for (int i: a)
        cout << i << ' ';
    cout << '\n';
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
