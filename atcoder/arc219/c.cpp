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

#define assert(v) do { if (!(v)) { __builtin_trap(); } } while (0)

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// ARC219C: Traveling Door-to-Door Salesman (Elevator)
void solve()
{
    int h, w, n;
    cin >> h >> w >> n;
    vector<pair<int, int>> vec(n);
    for (int i = 0; i < n; ++i) {
        cin >> vec[i].xx >> vec[i].yy;
    }

    sort(vec.begin(), vec.end());

    map<int, vector<int>> mp;
    for (int i = 0; i < n; ++i) {
        auto [r, c] = vec[i];
        mp[r].push_back(c);
    }

    vector<int> a, b;
    ll ans = 0;
    ll sum = 0;
    vector<int> costs;
    for (auto &[row, v]: mp) {
        ans += 2*(v.back() - 1);
        int gap = w - v.back() - 1;
        int last = 1;
        for (int x: v) {
            gap = max(gap, x - last - 1);
            last = x;
        }

        int cost = 2*(w - gap - 2);
        costs.push_back(cost);
        sum += cost;
    }

    sort(costs.begin(), costs.end());
    reverse(costs.begin(), costs.end());
    for (int i = 0; i < (int)costs.size(); ++i) {
        int cost = costs[i];
        sum -= cost;
        if (i % 2 == 0 || i == 0) {
            int total_cost = i * (w-1) + 2*(w-1) + sum;
            ans = min(ans, total_cost);
        } else {
            int total_cost = i * (w-1) + (w-1) + sum;
            ans = min(ans, total_cost);
        }
    }

    cout << ans << '\n';
}

int T = 1;
int32_t main(void)
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    while(T--)
        solve();

    return 0;
}
