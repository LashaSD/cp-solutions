#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll

// ABC417D: Takahashi's Expectation
void solve()
{
    int n; cin >> n;
    vector<pair<int, pair<int, int>>> vec(n);
    for (auto& p: vec) {
        cin >> p.first >> p.second.first >> p.second.second;
    }

    ll b_sum = 0;
    ll mx = vec.front().first;
    for (int i = 0; i < n; ++i) {
        int p = vec[i].first;
        mx = max(mx, p + b_sum);
        b_sum += vec[i].second.second;
    }
    
    map<ll, ll> memo;

    int q; cin >> q;
    vector<int> q_vec(q);
    for (int& x: q_vec)
        cin >> x;

    for (int x: q_vec) {
        if (x > mx) {
            cout << max(0ll, x - b_sum) << ' ';
            continue;
        } else if (memo[x] > 0) {
            cout << memo[x] - 1 << ' ';
            continue;
        }

        ll res = x;

        for (int i = 0; i < n; ++i) {
            ll p = vec[i].first;
            ll a = vec[i].second.first;
            ll b = vec[i].second.second;

            if (p >= res) {
                res += a;
            } else {
                res = max(0ll, res - b);
            }
        }

        memo[x] = res + 1;
        cout << res << ' ';
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
