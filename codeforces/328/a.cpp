#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

// 328A: IQ Test
void solve()
{
    double a, b, c, d;
    cin >> a >> b >> c >> d;


    int diff = b - a;
    if (c - b == diff && d - c == diff) {
        cout << d + diff << '\n';
        return;
    }

    double q = b / a;
    if (c / b == q && d / c == q) {
        float ans = d * q;
        if (ans == (int)ans) {
            cout << d * q << '\n';
            return;
        }
    }

    cout << 42 << '\n';
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
