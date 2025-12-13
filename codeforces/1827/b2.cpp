#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 1827B2: Range Sorting (Hard Version)
void solve()
{
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<pair<int, int>> vec(n);
    for (int i = 0; i < n; ++i) {
        vec[i] = {a[i], i};
    }

    sort(vec.begin(), vec.end());

    set<int> le, gr;
    for (int i = 0; i < n; ++i) {
        gr.insert(vec[i].yy);
    }

    ll sum = 0;
    for (int i = 0; i < n; ++i) {
        int idx = vec[i].yy;
        gr.erase(idx);

        int l, l0, r;

        auto l_it = le.upper_bound(idx);
        if (l_it == le.begin()) {
            le.insert(idx);
            continue;
        }
        l = *prev(l_it, 1);

        auto l0_it = gr.upper_bound(l);
        if (l0_it == gr.begin()) l0 = 0;
        else l0 = (*--l0_it) + 1;

        if (l_it == le.end()) r = n-1;
        else r = (*l_it) - 1;

        sum += (l - l0+1) * (r - idx + 1);

        le.insert(idx);
    }

    ll m = 0;
    for (int i = 1; i <= n; ++i) {
        m += ((n+i+1)*(n-i) / 2) - (n-i)*i;
    }

    cout << m - sum << '\n';
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
