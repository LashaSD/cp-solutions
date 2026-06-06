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

// 2226D: Reserved Reversals
void solve()
{
    int n; cin >> n;
    vector<int> vec(n);
    for (int i = 0; i < n; ++i) {
        cin >> vec[i];
    }

    vector<int> a, b;
    const int mn_inf = LLONG_MAX;
    const int mx_inf = LLONG_MIN;
    int mna = mn_inf, mxa = mx_inf;
    int mnb = mn_inf, mxb = mx_inf;
    for (int i = 0; i < n; ++i) {
        if (vec[i] % 2 == 0) {
            a.push_back(vec[i]);
            mxa = max(mxa, vec[i]);
            mna = min(mna, vec[i]);
        } else {
            b.push_back(vec[i]);
            mxb = max(mxb, vec[i]);
            mnb = min(mnb, vec[i]);
        }
    }

    vector<int> &curr = a;
    int mn = mnb, mx = mxb;
    for (int rep = 0; rep < 2; ++rep) {
        if (curr.size() != 0) {
            int curr_mx = curr[0];
            for (int i = 1; i < (int)curr.size(); ++i) {
                int x = curr[i];
                if (x >= curr_mx) {
                    curr_mx = x;
                } else {
                    if (
                        (mn == mn_inf || mn > x)
                        && (mx == mx_inf || mx < curr_mx)
                    ) {
                        cout << "NO\n";
                        return;
                    }
                }
            }
        }

        mn = mna;
        mx = mxa;
        curr = b;
    }

    cout << "YES\n";
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
