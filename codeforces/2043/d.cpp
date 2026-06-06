#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <cstdint>
#include <set>
#include <algorithm>
#include <assert.h>
#include <functional>
#include <map>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2155D: Batteries
void solve()
{
    int n; cin >> n;
    const int inf = LLONG_MAX;
    for (int j = 1; j < inf; ++j) {
        for (int i = 0; i < n; ++i) {
            int k = (i + j) % n;
            cout << i + 1 << ' ' << k + 1 << '\n';
            cout.flush();

            int x; cin >> x;
            if (x) return;
            if (x == -1) {
                exit(1);
            }
        }
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
