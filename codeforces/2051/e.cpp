#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2051E: Best Price
void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> l(n), r(n);
    for (int i = 0; i < n; ++i) {
        cin >> l[i];
    }

    for (int i = 0; i < n; ++i) {
        cin >> r[i];
    }

    vector<pair<int, int>> vec;
    for (int i = 0; i < n; ++i) {
        vec.push_back({l[i], 0});
        vec.push_back({r[i], 1});
    }

    sort(vec.begin(), vec.end());
    int bad = 0, passed = 0;
    ll ans = 0;
    int i = 0;
    int N = vec.size();
    while (i < N) {
        auto [x, closed] = vec[i];
        if (!closed) {
            int j = i;
            while ((j+1) < N && vec[j+1].xx == x && vec[j+1].yy == closed) j++;
            if (bad <= k) {
                ans = max(ans, x * (n - passed));
            }

            bad += j - i + 1;
            i = j+1;
        }

        if (closed) {
            int j = i;
            while ((j+1) < N && vec[j+1].xx == x && vec[j+1].yy == closed) j++;
            if (bad <= k) {
                ans = max(ans, x * (n - passed));
            }

            bad -= j - i + 1;
            passed += j - i + 1;
            i = j+1;
        }
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
