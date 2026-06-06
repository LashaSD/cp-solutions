#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <cstdint>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2206H: Reflect Sort
void solve()
{
    int n; cin >> n;
    vector<int> vec(n);
    for (int i = 0; i < n; ++i) {
        cin >> vec[i];
    }

    vector<int> d(n-1);
    int diff_sum = 0;
    int g = 0;
    for (int i = 1; i < n; ++i) {
        g = gcd(g, abs(vec[i] - vec[i-1]));
        diff_sum += abs(vec[i] - vec[i-1]);
    }
    g *= 2;

    int mn = vec[0];
    if (g > 0) {
        mn = vec[0] % g;
        if (mn == 0)
            mn = g;
    }

    int ans = mn + diff_sum;
    cout << ans << '\n';
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
