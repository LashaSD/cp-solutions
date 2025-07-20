#include <bits/stdc++.h>
#include <cassert>
#include <cmath>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

// 1327C: Game with Chips
void solve()
{
    int n, m;
    cin >> n >> m;

    vector<char> path;
    path.reserve(2*n*m);

    for (int i = 0; i < (m-1); ++i)
        path.push_back('L');

    for (int i = 0; i < (n-1); ++i)
        path.push_back('U');

    bool trigger = true;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < (m-1); ++j) {
            if (trigger)
                path.push_back('R');
            else
                path.push_back('L');
        }

        if (i < (n-1)) path.push_back('D');
        trigger = !trigger;
    }

    cerr << path.size() << ' ' << 2*n*m << '\n';
    assert((path.size() <= 2*n*m));

    cout << path.size() << '\n';
    for (char c: path) cout << c;
    cout << '\n';
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
