#include <bits/stdc++.h>
#include <numbers>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

int f(int l, int r)
{
    cout << "? " << l << ' ' << r << '\n';
    cout.flush();
    int t; cin >> t;
    return t;
}

// 2037E: Kachina's Favorite Binary String
void solve()
{
    int n; cin >> n;
    int last = f(1, n);
    if (last == 0) {
        cout << "! IMPOSSIBLE\n";
        cout.flush();
        return;
    }

    vector<char> ans(n+1, '?');
    int j = -1;
    for (int i = 2; i <= n; ++i) {
        int curr;
        if (i == n) {
            curr = 0;
        } else {
            curr = f(i, n);
        }

        if (curr != last) {
            ans[i-1] = '0';
        } else if (curr == last) {
            ans[i-1] = '1';
        }

        if (curr == 0) {
            j = i;
            break;
        }

        last = curr;
    }

    for (; j <= n; ++j) {
        if (last > 0) 
            ans[j] = '1';
        else
            ans[j] = '0';

        last--;
    }

    cout << "! ";
    for (int i = 1; i <= n; ++i) {
        cout << ans[i];
    }
    cout << '\n';
    cout.flush();
}

int T = 1;
int32_t main(void)
{
    cin >> T;
    while(T--)
        solve();

    return 0;
}
