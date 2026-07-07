#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <cstdint>
#include <set>
#include <algorithm>
#include <functional>
#include <map>

#define assert(v) do { if (!(v)) { *(int*)0 = 0; } } while (0)

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2231D: Maximum Prefix Sums
void solve()
{
    int n; cin >> n;
    string s; cin >> s;
    for (int i = 0; i < n; ++i) {
        s[i] -= '0';
    }

    vector<int> oa(n), oc(n);
    for (int i = 0; i < n; ++i) {
        cin >> oa[i];
    }

    for (int i = 0; i < n; ++i) {
        cin >> oc[i];
    }

    const int inf = 1e12;
    vector<int> b(n, inf);
    b[0] = oc[0];
    for (int i = 1; i < n; ++i) {
        if (oc[i] != oc[i-1]) {
            b[i] = oc[i];
        }
    }

    vector<int> a = oa;
    a[0] = oc[0];

    int l = 0, r = 1;
    while (r < n) {
        while (r < n && b[r] == inf) {
            r++;
        }

        int save_r = r;

        if (r == n) {
            bool found = false;
            for (int i = l+1; i < n; ++i) {
                if (!s[i]) {
                    if (!found) {
                        found = true;
                        a[i] = -inf;
                    } else {
                        a[i] = 0;
                    }
                }
            }
            break;
        }

        while (r > l && s[r]) {
            b[r-1] = b[r] - a[r];
            r--;
        }

        if (l == r) {
            l = save_r;
            r = save_r + 1;
            continue;
        }

        bool found = false;
        for (int i = l+1; i <= r-1; ++i) {
            if (!s[i]) {
                if (!found) {
                    found = true;
                    a[i] = -inf;
                } else {
                    a[i] = 0;
                }
            }

            b[i] = b[i-1] + a[i];
        }

        a[r] = b[r] - b[r-1];
        l = save_r;
        r = save_r + 1;
    }

    ll sum = 0;
    ll mx = LLONG_MIN;
    for (int i = 0; i < n; ++i) {
        sum += a[i];
        mx = max(mx, sum);
        if (mx != oc[i] || (s[i] && a[i] != oa[i])) {
            cout << "NO\n";
            return;
        }
    }

    cout << "YES\n";
    for (int i = 0; i < n; ++i) {
        cout << a[i] << ' ';
    }
    cout << '\n';
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


