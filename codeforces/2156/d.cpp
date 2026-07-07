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

#define assert(v) do { if (!(v)) { *(int*)0 = 0; } } while (0)

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2156D: Find the Last Number
void solve()
{
    int n; cin >> n;

    int logn = 63 - __builtin_clzll(n);

    // a = indices
    // b = values
    vector<int> a, b;
    for (int i = 1; i <= n; ++i) {
        b.push_back(i);
        if (i < n) {
            a.push_back(i);
        }
    }

    int x = 0;
    vector<int> mark(n+1);
    for (int k = 0; k <= logn; ++k) {
        mark.assign(n+1, 0);

        int bit = (1ll << k);
        int f1 = 0, f2 = 0;
        for (int idx: a) {
            cout << "? " << idx << ' ' << bit << '\n';
            cout.flush();
            int a_is_on;
            cin >> a_is_on;
            if (a_is_on) {
                f1++;
                mark[idx] = 1;
            }
        }


        for (int v: b) {
            if ((v & bit) != 0) {
                f2++;
            }
        }

        bool x_is_on = f1 != f2;
        for (int i = 0; i < (int)a.size();) {
            int idx = a[i];
            if (mark[idx] != x_is_on) {
                swap(a[i], a.back());
                a.pop_back();
            } else {
                i++;
            }
        }

        for (int i = 0; i < (int)b.size();) {
            bool b_is_on = (b[i] & bit) != 0;
            if (b_is_on != x_is_on) {
                swap(b[i], b.back());
                b.pop_back();
            } else {
                i++;
            }
        }

        if (x_is_on) {
            x |= bit;
        }
    }

    cout << "! " << x << '\n';
    cout.flush();
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
