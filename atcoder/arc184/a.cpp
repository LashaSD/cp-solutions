#include <iostream>
#include <cassert>
#include <climits>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <functional>

using namespace std;
using ll = long long;

#define int ll

// non-counterfeit
int k = 1;

// returns a == b
bool query(int a, int b)
{
    cout << "? " << a << ' ' << b << '\n';
    cout.flush();
    int t; cin >> t;
    if (t == -1) exit(1);
    return t == 0;
}

bool is_counterfeit(int a)
{
    cout << "? " << k << ' ' << a << '\n';
    cout.flush();
    int t; cin >> t;
    if (t == -1) exit(1);
    return t == 1;
}

// ARC184A: Appraiser 
void solve()
{
    int n, m, __q;
    cin >> n >> m >> __q;
    vector<vector<bool>> g(5, vector<bool>(n+1));
    vector<vector<bool>> ok(5, vector<bool>(n+1));
    for (int i = 1; i <= n; ++i) {
        ok[0][i] = 1;
    }

    for (int h = 1; h <= 4; ++h) {
        int gap = (1ll << h);
        int i = 1, j = (gap >> 1) + 1;
        while (j <= n) {
            g[h][i] = query(i, j);
            ok[h][i] = g[h][i] & ok[h-1][i] & ok[h-1][i + gap/2];
            i += gap, j += gap;
        }
    }

    for (int i = 1; i <= n; i += 16) {
        if (ok[4][i]) {
            k = i;
            break;
        }
    }

    vector<int> ans;
    function<bool(int, int)> f = [&](int l, int r) {
        int h = 63 - __builtin_clzll(r - l + 1);
        if (ok[h][l]) return false;

        int mid = l + (r - l) / 2;
        if (ok[h-1][l] && ok[h-1][mid+1]) {
            int tl = -1, tr = -1;
            if (is_counterfeit(l)) {
                tl = l, tr = mid;
            } else {
                tl = mid+1, tr = r;
            }

            for (int i = tl; i <= tr; ++i) {
                ans.push_back(i);
            }

            return (tl == l);
        }

        bool l_is_c = 0, m_is_c = 0;
        if (!ok[h-1][l])
            l_is_c = f(l, mid);

        if (!ok[h-1][mid+1])
            m_is_c = f(mid+1, r);

        if (ok[h-1][l] && !ok[h-1][mid+1]) {
            if (m_is_c == g[h][l]) {
                l_is_c = 1;
                for (int i = l; i <= mid; ++i) {
                    ans.push_back(i);
                }
            }
        }

        if (!ok[h-1][l] && ok[h-1][mid+1]) {
            if (l_is_c == g[h][l]) {
                for (int i = mid+1; i <= r; ++i) {
                    ans.push_back(i);
                }
            }
        }

        return l_is_c;
    };

    for (int i = 1; i + 15 <= n; i += 16) {
        f(i, i + 15);
    }

    if (m - (int) ans.size() == 8) {
        for (int i = n-7; i <= n; ++i) {
            ans.push_back(i);
        }
    } else {
        f(n - 7, n);
    }

    assert((int) ans.size() == m);
    cout << "! ";
    for (int i = 0; i < (int) ans.size(); ++i) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
    cout.flush();
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
