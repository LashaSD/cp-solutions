#include <bits/stdc++.h>
#include <cassert>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

// 1660E: Matrix and Shifts
void solve()
{
    int n; cin >> n;
    vector<vector<int>> vec(n, vector<int>(n));
    int one_cnt = 0;
    for (int i = 0; i < n; ++i) {
        string s; cin >> s;
        for (int j = 0; j < n; ++j) {
            int t = s[j] - '0';
            if (t == 1)
                one_cnt++;
            vec[i][j] = t;
        }
    }

    int mx = 0;
    for (int k = 0; k < n; ++k) {
        int ones = 0;
        for (int i = k, j = 0; j < n; j++, i = (i + 1) % n) {
            if (vec[i][j] == 1) {
                ones++;
            }
        }

        mx = max(mx, ones);
    }

    for (int k = 0; k < n; ++k) {
        int ones = 0;
        for (int i = 0, j = k; i < n; i++, j = (j + 1) % n) {
            if (vec[i][j] == 1) {
                ones++;
            }
        }

        mx = max(mx, ones);
    }

    cout << (n - mx) + (one_cnt - mx) << endl;
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
