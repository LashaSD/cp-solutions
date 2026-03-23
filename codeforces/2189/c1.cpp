#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2189C1: XOR Convenience (Easy Version)
void solve()
{
    int n; cin >> n;
    cout << ((n^1) > n ? n : n^1) << ' ';
    for (int i = 2; i <= n-1; ++i) {
        cout << (i ^ 1) << ' ';
    }
    cout << 1 << '\n';
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
