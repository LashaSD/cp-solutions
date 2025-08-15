#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

const ll MOD = 998244353LL;

const int MAX_N = 25e5;
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

ll C(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD;
}

// ARC143B: Counting Grids
void solve()
{
    int n; cin >> n;
    ll N = n*n;
    ll K = 2*n - 1;
    ll M = (K - 1) / 2;

    ll cell_sorted_cnt = C(N, K);
    ll cell_sorted_combinations = ((cell_sorted_cnt % MOD) * ((fact[M] % MOD) * (fact[M] % MOD) % MOD)) % MOD;
    ll rest = fact[N - (2*n - 1)] % MOD;
    ll cell_tot = ((cell_sorted_combinations % MOD) * (rest % MOD)) % MOD;
    ll ruined_cnt = (cell_tot * N) % MOD;

    ll ans = (MOD + (fact[N] - ruined_cnt)) % MOD;
    cout << ans << '\n';
}

int T = 1;
int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    precompute();

    // cin >> T;
    while(T--)
        solve();
    return 0;
}
