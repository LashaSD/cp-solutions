#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2189C2: XOR Convenience (Hard Version)
void solve()
{
    int n; cin >> n;
    if (__builtin_popcountll(n) == 1) {
        cout << -1 << '\n';
        return;
    }

    int highbit = 63 - __builtin_clzll(n);
    int x;
    for (int i = (1ll << (highbit-1)); i > 0; i >>= 1) {
        if ((n & i) != 0) {
            x = i;
            break;
        }
    }

    vector<int> ans(n+1);
    ans[1] = n^1;
    for (int i = 2; i <= n; ++i) {
        ans[i] = i^1;
    }
    ans[n] = 1;

    if ((n ^ 1) > n) {
        ans[1] = x^1;
        ans[x] = n;
    }

    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
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
