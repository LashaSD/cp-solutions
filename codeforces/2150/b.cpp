#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll

const int MOD = 998244353;

const int MAXN = 3e5 + 5;              
ll fac[MAXN + 1], ifac[MAXN + 1];

ll pow_mod(ll base, ll exp, ll mod){
    ll res = 1 % mod;
    while (exp > 0){
        if (exp & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

void precompute(){
    fac[0] = 1;
    for (int i = 1; i <= MAXN; ++i) fac[i] = fac[i - 1] * i % MOD;

    ifac[MAXN] = pow_mod(fac[MAXN], MOD - 2, MOD);
    for (int i = MAXN; i >= 1; --i) ifac[i - 1] = ifac[i] * i % MOD;
}

ll C(int n, int k){
    if (k < 0 || k > n || n > MAXN) return 0;
    return fac[n] * ifac[k] % MOD * ifac[n - k] % MOD;
}

// 2150B: Grid Counting
void solve()
{
    int n; cin >> n;
    vector<int> vec(n);
    for (int& x: vec)
        cin >> x;

    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += vec[i];
    }

    if (sum != n) {
        cout << 0 << '\n';
        return;
    }

    int reserve = 0;
    int width = n;
    for (int i = 0; i < n && width > 0; ++i, width -= 2) {
        int x = vec[i];
        int check_width = (width == 1 ? 1 : 2);
        if ((x + reserve) < check_width) {
            cout << 0 << '\n';
            return;
        } 

        reserve += x;
        reserve -= check_width;

        if (x > width) {
            cout << 0 << '\n';
            return;
        }
    }
    
    for (int i = (n + 1) / 2; i < n; ++i) {
        if (vec[i] > 0) {
            cout << 0 << '\n';
            return;
        }
    }

    int ans = 1;
    int k = 0;
    width = (n % 2 == 0 ? 2 : 1);
    for (int i = ((n + 1) / 2) - 1; i >= 0; --i, width += 2) {
        int x = vec[i];
        ans = (ans * C(width - k, x)) % MOD;
        k += x;
    }

    cout << ans << '\n';
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
