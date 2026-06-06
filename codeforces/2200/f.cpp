#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <cstdint>
#include <set>
#include <algorithm>
#include <functional>
#include <map>

#define assert(v) do { if (!(v)) { *(int*)0 = 0; } } while (0)

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2200F: Mooclear Reactor 2
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> vec(n);

    for (int i = 0; i < n; ++i) {
        cin >> vec[i].xx >> vec[i].yy;
    }

    vector<pair<int, int>> qvec(m);
    for (int i = 0; i < m; ++i) {
        cin >> qvec[i].xx >> qvec[i].yy;
    }

    sort(vec.begin(), vec.end(), [&](auto a, auto b) {
        return make_pair(a.yy, a.xx) > make_pair(b.yy, b.xx);
    });

    vector<int> opt(n+2);

    multiset<int> mt;
    ll sum = 0;
    int it = 0;
    int mx = 0;
    for (int y = n+1; y >= 1; --y) {
        while (it < n && vec[it].yy >= (y - 1)) {
            mt.insert(vec[it].xx);
            sum += vec[it].xx;
            it++;
        }

        while (mt.size() > y) {
            sum -= *mt.begin();
            mt.erase(mt.begin());
        }

        mx = max(mx, sum);
        opt[y] = sum;
        if (mt.size() == y) {
            opt[y] -= *mt.begin();
        }
    }

    vector<int> pref(n+2);
    pref[1] = opt[1];
    for (int i = 2; i <= n+1; ++i) {
        pref[i] = max(pref[i-1], opt[i]);
    }

    for (int i = 0; i < m; ++i) {
        auto [x, y] = qvec[i];

        int ans = max(mx, pref[y+1] + x);
        cout << ans << ' ';
    }
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
