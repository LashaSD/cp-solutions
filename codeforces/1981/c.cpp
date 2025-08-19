#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

const int INF = 2e9;

void fill_seg(vector<int>& ret, int x, int y, int k)
{
    if (x < y) swap(x, y);

    int x_mask = x >> (__lg(x) - __lg(y));
    int extra = __lg(x_mask ^ y);

    for (int i = 1; i <= (1 << extra); i <<= 1) {
        y >>= 1, k--;
        ret.push_back(y);
    }

    for (int i = 0; i < k; ++i) {
        if (y > x) {
            // x is 1
            y >>= 1;
            ret.push_back(y);
        } else if (y == x) {
            if (x == 1)
                y <<= 1;
            else
                y >>= 1;

            ret.push_back(y);
        } else {
            y <<= 1;
            y += (x >> (__lg(x) - __lg(y)) ^ y);
            ret.push_back(y);
        }
    }
}

// 1981C: Turtle and an Incomplete Sequence
void solve()
{
    int n; cin >> n;
    vector<int> vec(n), ans(n);
    for (int i = 0; i < n; ++i) {
        cin >> vec[i];
        ans[i] = vec[i];
    }

    int l = 0, r = n-1;
    while (l < n && vec[l] == -1) l++;
    while (r >= 0 && vec[r] == -1) r--;

    // all -1
    if (l == n) {
        ans[0] = 1;
        cout << 1 << ' ';
        for (int i = 1; i < n; ++i) {
            cout << ((i % 2 == 1) ? 2 : 1) << ' ';
        }
        cout << '\n';
        return;
    }

    if (l > 0) {
        l--;
        int up = (vec[l+1] == 1) ? vec[l+1] * 2 : vec[l+1] / 2;
        int down = (vec[l+1] == 1) ? up / 2 : up * 2;
        bool f = true;
        while (l >= 0) {
            ans[l] = (f ? up : down);
            f = !f;
            l--;
        }
    }

    if (r < (n-1)) {
        r++;
        int up = (vec[r-1] == 1) ? vec[r-1] * 2 : vec[r-1] / 2;
        int down = (vec[r-1] == 1) ? up / 2 : up * 2;
        bool f = true;
        while (r < n) {
            ans[r] = (f ? up : down);
            f = !f;
            r++;
        }
    }

    for (int l = 0, r = 0; ; ) {
        while ((l+1) < n && ans[l+1] != -1) l++;
        r = l + 1;
        while (r < n && ans[r] == -1) r++;
        int len = r - l;
        if (r == n) break;

        vector<int> ret;
        fill_seg(ret, ans[l], ans[r], r - l);
        int x = ans[l], y = ans[r];
        auto it = ret.begin();
        if (x <= y) {
            for (int t = l+1; t < r; t++) ans[t] = *it++;
        } else {
            for (int t = r-1; t > l; t--) ans[t] = *it++;
        }
    }

    for (int i = 0; i < (n-1); ++i) {
        if (ans[i] <= 0 || ans[i] > 1e9) {
            cout << -1 << '\n';
            return;
        }
        else if (ans[i]*2 != ans[i+1] &&
            ans[i]/2 != ans[i+1] &&
            ans[i+1]*2 != ans[i] &&
            ans[i+1]/2 != ans[i])
        {
            cout << -1 << '\n';
            return;
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << ans[i] << ' ';
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
