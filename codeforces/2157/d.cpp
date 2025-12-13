#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2157D: Billion Players Game
void solve()
{
    int n; cin >> n;
    int l, r;
    cin >> l >> r;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    sort(a.begin(), a.end());
    int med = min(r, max(l, a[n/2]));
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans += abs(a[i] - med);
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
