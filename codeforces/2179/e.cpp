#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <cstdint>
#include <set>
#include <algorithm>
#include <assert.h>
#include <functional>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2179E: Blackslex and Girls
void solve()
{
    int n, x, y;
    cin >> n >> x >> y;
    string s; cin >> s;
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
    }

    int P = 0;
    int lx = x, ly = y;
    int lp = 0;
    for (int i = 0; i < n; ++i) {
        P += p[i];
        int mn = p[i] / 2 + 1;
        lp += p[i] - mn;
        if (s[i] == '0') {
            lx -= mn;
        } else {
            ly -= mn;
        }

        if (lx < 0 || ly < 0) {
            cout << "NO\n";
            return;
        }
    }

    if (x + y == P) {
        cout << "YES\n";
        return;
    } else if (x + y < P) {
        cout << "NO\n";
        return;
    }

    int c0 = count(s.begin(), s.end(), '0');
    int c1 = count(s.begin(), s.end(), '1');
    if (c0 > 0 && c1 > 0) {
        cout << "YES\n";
        return;
    }

    if (c0 > 0) {
        swap(x, y);
    }

    if (x + n <= y) {
        cout << "YES\n";
        return;
    } else {
        cout << "NO\n";
        return;
    }
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
