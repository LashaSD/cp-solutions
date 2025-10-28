#include <iostream>
#include <cassert>
#include <climits>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <map>

using namespace std;
using ll = long long;
using ull = unsigned long long;

#define int ll

// 1893C: Freedom of Choice
void solve()
{
    int m; cin >> m;
    vector<vector<int>> a(m);
    vector<vector<int>> c(m);
    vector<pair<int, int>> bounds(m);
    for (int i = 0; i < m; ++i) {
        int n, l, r; 
        cin >> n >> l >> r;
        bounds[i] = make_pair(l, r);
        a[i].reserve(n);
        c[i].reserve(n);

        for (int j = 0; j < n; ++j) {
            int x; cin >> x;
            a[i].push_back(x);
        }

        for (int j = 0; j < n; ++j) {
            int x; cin >> x;
            c[i].push_back(x);
        }
    }

    int L = 0, R = 0;
    int N = 0;
    for (int i = 0; i < m; ++i) {
        L += bounds[i].first;
        R += bounds[i].second;
        N += (int) a[i].size();
    }

    map<int, pair<int, int>> mp;
    map<int, int> cnt;
    int tot_sum = 0;
    for (int i = 0; i < m; ++i) {
        auto [l, r] = bounds[i];
        tot_sum += r;

        int tot = 0;
        for (int j = 0; j < (int) a[i].size(); ++j) {
            tot += c[i][j];
        }

        for (int j = 0; j < (int) a[i].size(); ++j) {
            int x = a[i][j];
            int f = c[i][j];

            if (x >= L && x <= R) {
                int others = tot - f;

                int xs = 0;
                int total = 0;

                if (others < l) {
                    xs = l - others;
                    total = l;
                } else {
                    total = min(r, others);
                }

                auto& p = mp[x];
                p.first += xs;
                p.second += total;

                cnt[x] += r;
            }
        }
    }

    if (R - L > N) {
        cout << 0 << '\n';
        return;
    }

    int ans = LLONG_MAX;
    for (int x = L; x <= R; ++x) {
        if (cnt[x] == 0) {
            cout << 0 << '\n';
            return;
        }

        auto [y, len] = mp[x];
        len += (tot_sum - cnt[x]);
        // cerr << "DBG: " << x << ' ' << y << ' ' << len << '\n';
        ans = min(ans, y + max(0ll, x - len));
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
