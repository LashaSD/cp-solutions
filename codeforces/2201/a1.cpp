#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2201A1: Lost Civilization (Easy Version)
void solve()
{
    int n; cin >> n;
    vector<int> vec(n);
    for (int i = 0; i < n; ++i) {
        cin >> vec[i];
    }

    int a = 0;
    ll ans = 1;
    for (int i = 1; i < n; ++i) {
        if (vec[i] - vec[i-1] > 1) {
            ans++;
            a = i;
        }

        if (vec[i] <= vec[i-1] && vec[i] <= vec[a]) {
            ans++;
            a = i;
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
