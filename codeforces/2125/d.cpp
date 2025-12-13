#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

const int mod = 998244353;

int binpow(int base, int pow)
{
    int res = 1;
    base = base % mod;
    while (pow > 0) {
        if (pow & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        pow >>= 1;
    }
    return res;
}

static inline int inv(int x)
{
    return binpow(x, mod-2);
}

// 2125D: Segments Covering
void solve()
{
    int n, m;
    cin >> n >> m;
    using P = pair<int, int>;
    vector<pair<P, P>> vec(n);
    for (int i = 0; i < n; ++i) {
        cin >> vec[i].xx.xx >> vec[i].xx.yy;
        cin >> vec[i].yy.xx >> vec[i].yy.yy;
    }

    int failure = 1;
    for (int i = 0; i < n; ++i) {
        int p = vec[i].yy.xx;
        int q = vec[i].yy.yy;
        failure = failure * ((q-p) * inv(q) % mod) % mod;
    }

    vector<int> dp(m+1);
    dp[0] = failure;
    sort(vec.begin(), vec.end(), [&](auto& a, auto& b) {
                return a.xx.yy < b.xx.yy;
            });
    for (int i = 0; i < n; ++i) {
        int l = vec[i].xx.xx;
        int r = vec[i].xx.yy;
        int p = vec[i].yy.xx;
        int q = vec[i].yy.yy;

        int prob = (p * inv(q)) % mod;
        int rev = dp[l-1] * (q * inv(q - p) % mod) % mod;
        dp[r] = (dp[r] + (rev * prob % mod)) % mod;
    }

    cout << dp[m] << '\n';
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
