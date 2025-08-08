#include <algorithm>
#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;
#define int ll

// 1870D: Prefix Purchase
void solve()
{
    int n; cin >> n;
    vector<int> vec(n);
    for (int& it: vec)
        cin >> it;
    int k; cin >> k;

    vector<int> suff(n+1);
    suff[n] = vec.back();
    for (int i = n-1; i >= 1; --i) {
        suff[i] = min(suff[i+1], vec[i-1]);
    }

    dbg(suff);
    vector<int> ans(n);
    ans[0] = k / suff[1];
    int reserve = k % suff[1];
    for (int i = 1; i < n; ++i) {
        ll delta = suff[i+1] - suff[i];
        if (delta != 0) {
            ans[i] = min(ans[i-1], reserve / delta);
        } else {
            ans[i] = ans[i-1];
        }
        reserve -= delta * ans[i];
    }

    for (int i = 0; i < n; ++i)
        cout << ans[i] << ' ';
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
