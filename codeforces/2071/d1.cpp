#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2071D1: Infinite Sequence (Easy Version)
void solve()
{
    int n, x;
    cin >> n >> x >> x;
    vector<int> a(n+1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    vector<int> pref(n+1);
    for (int i = 1; i <= n; ++i) {
        pref[i] = pref[i-1] ^ a[i];
    }

    int v = 0;
    if (n % 2 == 0)
        v = pref[n / 2];
    
    function<int(int)> f = [&](int x) {
        if (x <= n)
            return a[x];

        int m = x / 2;
        if (m <= n)
            return pref[m];
        if (m % 2 == 0) {
            int y = f(m);
            return pref[n] ^ v ^ y;
        }

        return pref[n] ^ v;
    };

    cout << f(x) << '\n';
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
