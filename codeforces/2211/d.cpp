#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <cstdint>
#include <set>
#include <algorithm>
#include <functional>
#include <map>

#define assert(v) do { if (!(v)) { *(int*)0 = 0; } } while (0)

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

const int MOD = 1e9 + 7;
const int MAXN = 1e5 + 5;

vector<ll> fact(MAXN + 1), inv_fact(MAXN + 1);

ll modpow(ll base, ll exp) {
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
    for (int i = 1; i <= MAXN; i++)
        fact[i] = (fact[i - 1] * i) % MOD;

    inv_fact[MAXN] = modpow(fact[MAXN], MOD - 2);
    for (int i = MAXN; i > 0; i--)
        inv_fact[i - 1] = (inv_fact[i] * i) % MOD;
}

inline ll C(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD;
}

// 2211D: AND-array
void solve()
{
    int n; cin >> n;
    vector<int> b(n+1);
    for (int i = 1; i <= n; ++i) {
        cin >> b[i];
    }

    vector<pair<int, int>> s;
    s.push_back({b[n], n});
    for (int i = n-1; i >= 1; --i) {
        int val = 0;
        for (auto [x, f]: s) {
            val = (val + (x * C(f, i)) % MOD) % MOD;
        }
        int curs = (MOD + (b[i] - val)) % MOD;

        if (curs > 0) {
            s.push_back({curs, i});
        }
    }

    vector<int> ans(n);
    for (auto [x, f]: s) {
        for (int i = 0; i < f; ++i) {
            ans[i] |= x;
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
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


