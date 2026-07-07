#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <cstdint>
#include <set>
#include <cstdio>
#include <algorithm>
#include <functional>
#include <map>

#define assert(v) do { if (!(v)) { *(int*)0 = 0; } } while (0)

using namespace std;
using ll = long long;

#define xx first
#define yy second

using P = pair<int, int>;
const int inf = 1e9;

const int maxn = 2000005;
int y_pref[maxn], x_max_y[maxn], x_min_y[maxn];
int suff_min[maxn], suff_max[maxn];

// 2228D: Sanae, Cross and Color
void solve()
{
    int n; cin >> n;
    vector<P> vec(n);

    for (int i = 0; i <= n; ++i) {
        y_pref[i] = 0;
        x_max_y[i] = 0;
        x_min_y[i] = inf;
    }

    int maxx = 0;
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        maxx = max(maxx, x);
        y_pref[y] = 1;
        x_max_y[x] = max(x_max_y[x], y);
        x_min_y[x] = min(x_min_y[x], y);
    }

    for (int y = 1; y <= n; ++y) {
        y_pref[y] += y_pref[y-1];
    }

    vector<int> suff_min(n+2, inf), suff_max(n+2, 0);
    for (int x = maxx; x >= 0; --x) {
        suff_min[x] = min(x_min_y[x], suff_min[x+1]);
        suff_max[x] = max(x_max_y[x], suff_max[x+1]);
    }

    ll ans = 0;
    int pref_min = inf, pref_max = 0;
    for (int x = 1; x <= maxx; ++x) {
        if (x_max_y[x] == 0) continue;

        pref_min = min(x_min_y[x], pref_min);
        pref_max = max(x_max_y[x], pref_max);

        int max_y = min(pref_max, suff_max[x+1]);
        int min_y = max(pref_min, suff_min[x+1]);
        if (min_y < max_y) {
            int len = y_pref[max_y] - y_pref[min_y - 1];
            ans += len - 1;
        }
    }

    cout << ans << '\n';
}

int T = 1;
int32_t main(void)
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    cin >> T;
    while(T--)
        solve();

    return 0;
}


