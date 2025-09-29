#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll

const ll MOD = 998244353LL;

const int MAX_N = 500;
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
    int res = 1;
    for (int i = n; i > (n - k); --i) {
        res = res * i % MOD;
    }

    return inv_fact[k] * res % MOD;
}

// ARC134C: The Majority
void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> vec(n+1);
    for (int i = 1; i <= n; ++i)
        cin >> vec[i];


    int others = 0;
    for (int i = 2; i <= n; ++i) {
        others += vec[i];
    }

    int diff = vec[1] - (others + k);

    if (diff < 0) {
        cout << 0 << '\n';
        return;
    } 

    ll configs = 1;
    for (int i = 2; i <= n; ++i) {
        configs = configs * C(vec[i] + k - 1, k - 1) % MOD;
    }

    ll ans = configs * C(diff + k - 1, k - 1) % MOD;
    
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
