#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll

// 1730B: Meeting on the Line
void solve()
{
    int n; cin >> n;
    vector<int> a(n), t(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    for (int i = 0; i < n; ++i) {
        cin >> t[i];
    }

    auto f = [&](long double x0) {
        long double mx = 0;
        for (int i = 0; i < n; ++i) {
            long double x1 = a[i];
            long double dx = fabs(x1 - x0);
            mx = max(mx, t[i] + dx);
        }

        return mx;
    };

    long double eps = 1e-6;
    long double l = 0, r = 1e8 + 5;
    long double ans = -1;
    using ld = long double;

    while ((r - l) > eps) {
        ld mid = l + (r - l) / 2;

        ld fm = f(mid);
        ld f1 = f(mid - eps); 
        ld f2 = f(mid + eps);

        if (f1 > fm && fm < f2) {
            l = mid;
            break;
        }

        if (f1 < fm && fm < f2) {
            r = mid - eps;
        }

        if (f1 > fm && fm > f2) {
            l = mid + eps;
        }
    }

    cout << setprecision(10) << l << '\n';
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
