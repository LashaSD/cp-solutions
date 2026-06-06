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

// 2185G: Mixing MEXes
void solve()
{
    int n; cin >> n;
    vector<vector<int>> vec(n);
    vector<int> mx(n);
    map<int, int> mxf;
    ll mex_sum = 0;
    for (int i = 0; i < n; ++i) {
        int sz; cin >> sz;
        for (int j = 0; j < sz; ++j) {
            int x; cin >> x;
            vec[i].push_back(x);
        }

        sort(vec[i].begin(), vec[i].end());
        int mx1 = 0;
        for (int j = 0; j < sz; ++j) {
            if (vec[i][j] == mx1) {
                mx1++;
            } else if (vec[i][j] > mx1) {
                break;
            }
        }

        int mx2 = mx1 + 1;
        for (int j = 0; j < sz; ++j) {
            if (vec[i][j] == mx2) {
                mx2++;
            } else if (vec[i][j] > mx2) {
                break;
            }
        }

        mx[i] = mx1;
        mxf[mx1] += mx2 - mx1;
        mex_sum += mx1;
    }

    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        int sz = vec[i].size();
        for (int j = 0; j < sz; ++j) {
            int x = vec[i][j];
            ll curr_mx = mx[i];

            bool is_duplicate = 0;
            if (j > 0 && vec[i][j-1] == x) {
                is_duplicate = 1;
            }

            if (j < sz-1 && vec[i][j+1] == x) {
                is_duplicate = 1;
            }

            if (x <= curr_mx && !is_duplicate) {
                curr_mx = x;
            }

            ll other_mx = mex_sum - mx[i];
            ans += (curr_mx + other_mx) * (n - 1) + mxf[x];
        }
    }

    cout << ans << '\n';
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
