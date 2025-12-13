#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

int query(int l, int r)
{
    cout << "? " << l << ' ' << r << '\n';
    cout.flush();
    int x; cin >> x;
    return x;
}

// 2163D1: Diadrash (Easy Version)
void solve()
{
    int n, q;
    cin >> n >> q;
    const int inf = 1e9;
    vector<int> mxl(n+1, inf), mxr(n+1);
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        mxr[l] = max(mxr[l], r);
        mxl[r] = min(mxl[r], l);
    }

    int h1 = query(1, n / 2);
    int h2 = query(n / 2 + 1, n);

    int ans = 0;
    if (h1 > 0) {
        for (int i = 1; i <= n/2; ++i) {
            if (mxr[i] > 0)
                ans = max(ans, query(i, mxr[i]));
        }
    } else {
        for (int i = n/2+1; i <= n; ++i) {
            if (mxl[i] <= i)
                ans = max(ans, query(mxl[i], i));
        }
    }

    cout << "! " << ans << '\n';
    cout.flush();
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
