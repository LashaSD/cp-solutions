#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll

const int MOD = 998244353;
const int MAX_N = 4e5;
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
    for (int i = MAX_N; i > 0; --i) {
        inv_fact[i-1] = (i * inv_fact[i]) % MOD;
    }
}

// ARC189A: Reversi 2
void solve()
{
    int n; cin >> n;
    vector<int> vec(n);
    for (int& x: vec)
        cin >> x;

    vector<int> dp(n+1);
    dp[3] = 1;
    for (int i = 5; i <= n; i += 2) {
        dp[i] = ((i-2) * dp[i-2]) % MOD;
    }

    vector<int> segs;
    for (int c = 1, i = 1; i < n; ++i) {
        if (vec[i] == vec[i-1]) {
            c++;
        } 

        if (vec[i] != vec[i-1] || i == n-1) {
            if (c % 2 == 0 || vec[i] != ((i+1) % 2)) {
                cout << 0 << '\n';
                return;
            }

            segs.push_back(c);
            c = 1;
        }
    }

    int tot_ops = 0;
    int fillings = 1;
    int overcount = 1;
    for (int c: segs) {
        if (c == 1) continue;

        tot_ops += c/2;
        fillings = (fillings * dp[c]) % MOD;
        overcount = (overcount * fact[c/2]) % MOD;
    }

    ll inv_overcount = modPow(overcount, MOD - 2);

    // cerr << "FRAMES: " << fact[frames] << '\n';
    // cerr << "FILLINGS: " << fillings << '\n';
    int frames = fact[tot_ops];
    ll ans = (frames * fillings) % MOD;
    ans = (ans * inv_overcount) % MOD;

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
