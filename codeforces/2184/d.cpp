#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

const ll MOD = 998244353LL;
const int MAX_N = 33;
vector<ll> fact(MAX_N + 1), inv_fact(MAX_N + 1);

ll modPow(ll base, ll exp) {
    ll result = 1;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return result;
}

void precompute()
{
    fact[0] = 1;
    for (int i = 1; i <= MAX_N; i++)
        fact[i] = (fact[i - 1] * i) % MOD;

    inv_fact[MAX_N] = modPow(fact[MAX_N], MOD - 2);
    for (int i = MAX_N; i > 0; i--)
        inv_fact[i - 1] = (inv_fact[i] * i) % MOD;
}

inline ll C(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD;
}

// 2184D: Unfair Game
void solve()
{
    ll n, k;
    cin >> n >> k;

    ll ans = 0;
    ll n_msb = 63ll - __builtin_clzll(n);
    if (n_msb + __builtin_popcountll(n) <= k) {
        ans++;
    }

    for (int msb = n_msb-1; msb >= 0; --msb) {
        int mx = k - msb - 1;
        for (int pc = 0; pc <= min(msb, mx); ++pc) {
            ans += C(msb, pc);
        }
    }

    cout << n - ans << '\n';
}

int T = 1;
int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    precompute();

    cin >> T;
    while(T--)
        solve();

    return 0;
}
