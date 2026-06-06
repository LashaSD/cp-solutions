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

using P = pair<int, int>;

P inter(P a, P b)
{
    return {max(a.xx, b.xx), min(a.yy, b.yy)};
}

// 2180D: Insolvable Disks
void solve()
{
    int n; cin >> n;
    vector<int> vec(n);
    for (int i = 0; i < n; ++i) {
        cin >> vec[i];
    }

    if (n == 1) {
        cout << 0 << '\n';
        return;
    }

    vector<P> a(n);
    a[0].yy = vec[1] - vec[0];
    a[n-1].yy = vec[n-1] - vec[n-2];
    for (int i = 1; i < n-1; ++i) {
        a[i].yy = min(vec[i] - vec[i-1], vec[i+1] - vec[i]);
    }

    int l = 0;
    int ans = 0;
    for (int i = 1; i < n; ++i) {
        int d = vec[i] - vec[i-1];

        P possible_range = inter(a[i], {d - a[i-1].yy, d - a[i-1].xx});
        P range = inter(possible_range, a[i]);
        if (range.xx >= range.yy) {
            ans += i - l - 1;
            l = i;
            continue;
        }

        if (i == n-1) {
            ans += i - l;
        }

        a[i] = range;
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
