#include <algorithm>
#include <bits/stdc++.h>
#include <iomanip>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

// D - Maximum Product Strikes Back
void solve()
{
    int n; cin >> n;
    vector<int> vec(n);
    for (int i = 0; i < n; ++i) {
        cin >> vec[i];
    }

    vector<pair<int, int>> segs;
    {
        int i = 0;
        while (vec[i] == 0 && i < n) ++i;
        if (i == n) {
            cout << n << ' ' << 0 << '\n';
            return;
        }

        int start = i;
        for (i = 0; i < n; ++i) {
            if (vec[i] == 0 && start != -1) {
                segs.push_back({ start, i-1 });
                start = -1;
            } else if (start == -1 && vec[i] != 0) {
                start = i;
            }
        }

        if (start != -1) {
            dbg(start);
            segs.push_back({start, n-1});
        }
    }

    pair<int, int> best_seg = {n, n-1};
    int best_two_count = 0;
    for (int k = 0; k < (int) segs.size(); ++k) {
        pair<int, int> seg = segs[k];

        int l = seg.first, r = seg.second;
        int minus_count = 0, two_count = 0;
        for (int i = l; i <= r; ++i) {
            if (vec[i] < 0)
                minus_count++;
            if (abs(vec[i]) == 2)
                two_count++;
        }

        if (minus_count % 2 == 1) {
            int i = l, l_cnt = 0;
            while (i <= r) {
                if (abs(vec[i]) == 2)
                    l_cnt++;
                if (vec[i] < 0)
                    break;
                ++i;
            }

            int j = r, r_cnt = 0;
            while (j >= l) {
                if (abs(vec[j]) == 2)
                    r_cnt++;
                if (vec[j] < 0)
                    break;
                --j;
            }

            if (l_cnt < r_cnt) {
                two_count -= l_cnt;
                seg = { i+1, r };
            } else {
                two_count -= r_cnt;
                seg = { l, j-1 };
            }
        }

        if (best_two_count < two_count) {
            best_seg = seg;
            best_two_count = two_count;
        }
    }

    dbg(segs);
    dbg(best_seg);
    cout << best_seg.first << ' ' << n - 1 - best_seg.second << '\n';
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
