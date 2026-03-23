#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2163B: Siga ta Kymata
void solve()
{
    int n; cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
    }

    string x; cin >> x;
    int l = 0, r = n-1, t = -1, b = -1;
    for (int i = 0; i < n; ++i) {
        if (t == -1 || p[t] < p[i]) t = i;
        if (b == -1 || p[b] > p[i]) b = i;
    }

    string s(n, '0');
    auto op = [&](int l, int r) {
        int mn = min(p[l], p[r]);
        int mx = max(p[l], p[r]);
        for (int i = min(l, r); i < max(l, r); ++i) {
            if (mn < p[i] && p[i] < mx) {
                s[i] = '1';
            }
        }
    };

    op(l, b);
    op(b, r);
    op(l, t);
    op(t, r);
    op(b, t);

    for (int i = 0; i < n; ++i) {
        if (x[i] == '1' && s[i] == '0') {
            cout << "-1\n";
            return;
        }
    }

    l++, r++, b++, t++;
    cout << 5 << '\n';
    cout << l << ' ' << b << '\n';
    cout << b << ' ' << r << '\n';
    cout << l << ' ' << t << '\n';
    cout << t << ' ' << r << '\n';
    cout << min(b, t) << ' ' << max(b, t) << '\n';
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
