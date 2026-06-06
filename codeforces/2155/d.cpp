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

// 2043D: Problem about GCD
void solve()
{
    int l, r, g;
    cin >> l >> r >> g;
    l = (l + g - 1) / g;
    r = r / g;
    int gap = r-l;
    while (gap >= 0) {
        int diff = (r-l) - gap;
        for (int li = 0; li <= diff; ++li) {
            int curr_l = l + li;
            int curr_r = curr_l + gap;
            if (gcd(curr_l, curr_r) == 1) {
                cout << curr_l*g << ' ' << curr_r*g << '\n';
                return;
            }
        }
        gap--;
    }

    cout << "-1 -1\n";
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
