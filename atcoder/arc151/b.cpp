#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MOD = 998244353;

// ARC151B: A < AP
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> vec(n);
    for (int& x: vec)
        cin >> x;

    int set_cnt = 0;
    vector<int> p(n+1), s(n+1);
    for (int i = 1; i <= n; ++i) {
        p[i] = i;
        s[i] = 1;
        set_cnt++;
    }

    function<int(int)> head = [&](int u) {
        if (p[u] == u) return u;
        return p[u] = head(p[u]);
    };

    auto merge = [&](int u, int v) {
        u = head(u);
        v = head(v);
        if (u != v) {
            p[u] = v;
            s[u] += s[v];
            set_cnt--;
        }
    };

    vector<ll> m_pow(n+1, 0);
    m_pow[0] = 1;
    for (int i = 1; i <= n; ++i) {
        m_pow[i] = (m_pow[i-1] * m) % MOD;
    }

    ll pairs = (((ll) m * (ll) (m-1)) / 2) % MOD;
    ll ans = 0;
    for (int i = 1; i <= n; ++i) {
        int x = vec[i-1];
        // compute combinations where a[i] < a[x]
        int u = head(i);
        int v = head(x);
        if (i != x && u != v) {
            int cnt = set_cnt - 2;
            ans = (ans + (pairs * m_pow[cnt]) % MOD) % MOD;
        }
        // mark a[i] = a[x]
        merge(u, v);
    }

    cout << ans << '\n';
}

int T = 1;
int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // cin >> T;
    while(T--)
        solve();
    return 0;
}
