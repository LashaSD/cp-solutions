#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define xx first
#define yy second

using P = pair<int, int>;

// 1954E: Chain Reaction
void solve()
{
    int n; cin >> n;
    vector<int> a(n);
    int mx = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        mx = max(mx, a[i]);
    }

    vector<vector<P>> segs(2);
    vector<ll> ans(1e5 + 10);

    auto insert_segs = [&](int x) {
        swap(segs[0], segs[1]);
        segs.back().clear();
        int k = 1;
        while (k < x) {
            int p = (x - 1) / k;
            int r = (x - 1) / p;
            segs.back().push_back(make_pair(k, r));
            k = r + 1;
        }
        segs.back().push_back(make_pair(x, mx));
    };

    insert_segs(a[0]);
    for (auto [l, r]: segs[1]) {
        int x = a[0];
        int v = (x + l - 1) / l;
        ans[l] += v;
        ans[r+1] += -v;
    }

    for (int i = 1; i < n; ++i) {
        insert_segs(a[i]);
        const vector<P>& sx = segs[0];
        const vector<P>& sy = segs[1];
        int xi = 0, yi = 0;
        while (xi < (int) sx.size() && yi < (int) sy.size()) {
            auto [l1, r1] = sx[xi];
            auto [l2, r2] = sy[yi];

            int x = (a[i - 1] + l1 - 1) / l1;
            int y = (a[i] + l2 - 1) / l2;
            int v = max(0, y - x);

            int l3 = max(l1, l2);
            int r3 = min(r1, r2);
            if (l3 <= r3) {
                ans[l3] += v;
                ans[r3 + 1] += -v;
            }

            if (r1 < r2) {
                xi++;
            } else {
                yi++;
            }
        }
    }

    ll sum = ans[0];
    for (int i = 1; i <= mx; ++i) {
        sum += ans[i];
        cout << sum << ' ';
    }
    cout << '\n';
}

int T = 1;
int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //cin >> T;
    while(T--)
        solve();

    return 0;
}
