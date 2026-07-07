#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <cstdint>
#include <set>
#include <cstdio>
#include <algorithm>
#include <functional>
#include <map>

#define assert(v) do { if (!(v)) { __builtin_trap(); } } while (0)

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2148G: Farmer John's Last Wish
void solve()
{
    int n; cin >> n;
    vector<int> vec(n+1);
    for (int i = 1; i <= n; ++i) {
        cin >> vec[i];
    }

    vector<int> fr(n+1);
    vector<int> divs, prev_invalid;
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        int x = vec[i];
        divs.clear();
        for (int j = 1; j*j <= x; ++j) {
            if (x % j == 0) {
                divs.push_back(j);
                if (x / j != j) {
                    divs.push_back(x / j);
                }
            }
        }

        for (int d: divs) {
            fr[d]++;
            if (fr[d] < i) {
                ans = max(ans, fr[d]);
            }
        }

        for (int d: prev_invalid) {
            if (fr[d] < i) {
                ans = max(ans, fr[d]);
            }
        }

        prev_invalid.clear();
        for (int d: divs) {
            if (fr[d] == i) {
                prev_invalid.push_back(d);
            }
        }

        cout << ans << ' ';
    }
    cout << '\n';
}

int T = 1;
int32_t main(void)
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    cin >> T;
    while(T--)
        solve();

    return 0;
}
