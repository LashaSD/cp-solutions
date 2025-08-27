#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

const ll INF = 3e9;

// 363D: Renting Bikes
void solve()
{
    int n, m, reserve;
    cin >> n >> m >> reserve;
    vector<int> coins(n), costs(m);
    for (int& it: coins) cin >> it;
    for (int& it: costs) cin >> it;

    sort(costs.begin(), costs.end());
    sort(coins.begin(), coins.end());

    auto f = [&](int k) {
        k = min(m, k);
        ll r = n-1;
        ll total_coins = 0;
        ll required_reserve = 0;
        for (int i = k-1; i >= 0; --i) {
            if (r < 0) return (pair<ll,ll>){ 0ll, INF };
            ll cost = costs[i];
            ll coin = coins[r];
            required_reserve += max(0ll, cost - coin);
            total_coins += min(cost, coin);
            r--;
        }

        return (pair<ll, ll>) { total_coins, required_reserve };
    };

    int l = 0, r = m;
    pair<ll, ll> ans = {0, 0};
    while (l <= r) {
        int mid = l + (r - l) / 2;
        auto info = f(mid);
        ll total_coins = info.first;
        ll required_reserve = info.second;
        if (required_reserve <= reserve) {
            l = mid + 1;
            ans = { mid, max(0LL, total_coins - max(0ll, reserve - required_reserve)) };
        } else {
            r = mid - 1;
        }
    }

    cout << ans.first << ' ' << ans.second << '\n';
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
