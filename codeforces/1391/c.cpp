#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define xx first
#define yy second

const ll mod = 1e9 + 7;
const int maxN = 1e6 + 5;

vector<ll> fact(maxN + 1), inv_fact(maxN + 1);

ll modPow(ll base, ll exp) {
    ll result = 1;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

void precompute()
{
    fact[0] = 1;
    for (int i = 1; i <= maxN; i++)
        fact[i] = (fact[i - 1] * i) % mod;

    inv_fact[maxN] = modPow(fact[maxN], mod - 2);
    for (int i = maxN; i > 0; i--)
        inv_fact[i - 1] = (inv_fact[i] * i) % mod;
}

ll C(int n, int k) 
{
    if (k < 0 || k > n || n > maxN) return 0;
    return fact[n] * inv_fact[k] % mod * inv_fact[n - k] % mod;
}

// 1391C: Cyclic Permutations 
void solve()
{
    int n; cin >> n;
    int ans = fact[n], neg = 0;
    for (int i = 1; i <= n; ++i) {
        neg = (neg + C(n-1, i-1)) % mod;
    }

    ans = (mod + (ans - neg)) % mod;
    cout << ans << '\n';
}

int T = 1;
int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    precompute();

    //cin >> T;
    while(T--)
        solve();

    return 0;
}
