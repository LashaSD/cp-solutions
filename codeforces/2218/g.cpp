#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second
using P = pair<int, int>;

const int MOD = 676767677;

// 2218G: The 67th Iteration of "Counting is Fun"
void solve()
{
    int n, m;
    cin >> n >> m;
    const int INF = 1e9;
    vector<int> vec(n+2), f(m), ans(n+2);
    for (int i = 1; i <= n; ++i) {
        cin >> vec[i];
        f[vec[i]]++;
    }

    vector<int> pref(m);
    pref[0] = f[0];
    for (int i = 1; i < m; ++i)
        pref[i] = pref[i-1] + f[i];

    vec[0] = vec[n+1] = INF;

    for (int i = 1; i <= n; ++i) {
        int mn = min(vec[i-1], vec[i+1]);

        if (vec[i] == 0) {
            ans[i] = 1;
            continue;
        }

        if (mn >= vec[i]) {
            cout << 0 << '\n';
            return;
        }

        if (mn == vec[i] - 1) {
            ans[i] = pref[vec[i] - 1];
        } else {
            ans[i] = f[vec[i] - 1];
        }
    }

    ll ret = 1;
    for (int i = 1; i <= n; ++i) {
        ret = (ret * ans[i]) % MOD;
    }
    cout << ret << '\n';
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
