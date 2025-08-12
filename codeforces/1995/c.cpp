#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

#define int ll

const int MAX_N = 1e6;
int limits[MAX_N + 5];

void precompute()
{
    for (int i = 2; i <= MAX_N; ++i) {
        int cnt = 0;
        int x = i;
        while (x <= MAX_N) {
            x *= x;
            cnt++;
        }
        limits[i] = cnt;
    }
}

// x^(2^n) cmp y^(2^m)
bool cmp(int x, int n, int y, int m)
{
    if (n < m) {
        m -= n;
        n = 0;
        int lim = limits[y];
        if (m > lim) {
            return true;
        } else {
            int comp_y = y;
            for (int j = 0; j < m; ++j) {
                comp_y *= comp_y;
            }

            dbg(x, n, y, m);
            dbg(x, comp_y);
            return x <= comp_y;
        }
    } else {
        n -= m;
        m = 0;
        int lim = limits[x];
        if (n > lim) {
            return false;
        } else {
            int comp_x = x;
            for (int j = 0; j < n; ++j)
                comp_x *= comp_x;

            dbg(comp_x, y);
            return comp_x <= y;
        }
    }
}

// 1995C: Squaring
void solve()
{
    int n; cin >> n;
    vector<int> vec(n);
    for (int& i: vec)
        cin >> i;

    vector<int> powers(n);
    int ans = 0;
    for (int i = 1; i < n; ++i) {
        int x = vec[i-1];
        int y = vec[i];

        if (y == 1 && x > y) {
            cout << -1 << '\n';
            return;
        }

        dbg(cmp(1, 0, 1, 1));
        int l = 0, r = 1e6;
        int pow = 0;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            bool x_is_less = cmp(x, powers[i-1], y, mid);
            if (x_is_less) {
                r = mid-1;
                pow = mid;
            } else {
                l = mid+1;
            }
        }

        powers[i] = pow;
        ans += pow;
    }

    cerr << '\n';
    dbg(cmp(5, 1, 2, 2));
    dbg(powers);

    cout << ans << '\n';
}

int T = 1;
int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    precompute();

    cin >> T;
    while(T--)
        solve();
    return 0;
}
