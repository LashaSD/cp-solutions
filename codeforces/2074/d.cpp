#include <bits/stdc++.h>
#include <unordered_map>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;
using pii = pair<ll, ll>;

// 2074D: Counting Points
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<pii> vec(n);

    for (pii& a: vec)
        cin >> a.first;

    for (pii& a: vec)
        cin >> a.second;

    sort(vec.begin(), vec.end(), [](pii& a, pii& b) {
        return (a.first - a.second) < (b.first - b.second);
    });

    ll sum = 0;
    // pair<int, int> = {bot, top}, which is range [bot, top)
    unordered_map<int, pii> range;
    for (auto &[center_x, radius]: vec) {
        ll r = radius;
        for (ll x = center_x - r; x <= center_x + r; x++) {
            pii& loc_range = range[x];
            ll diff_x = abs(center_x - x);
            ll r_sq = r*r;
            ll x_sq = diff_x*diff_x;
            ll y = sqrt(abs(r_sq - x_sq));

            int bot = -y;
            int top = y;

            ll inc = max(0ll, (top - bot + 1) - (loc_range.second - loc_range.first));
            sum += inc;
            dbg(x, r, bot, top, inc);
            loc_range.first = min(loc_range.first, -y);
            loc_range.second = max(loc_range.second, y + 1);
        }
    }

    cout << sum << '\n';
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
