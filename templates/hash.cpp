#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int P = 31;
const int MOD = 1e9 + 9;
const int MAX_N = 2e5 + 5;

ll p_pow[MAX_N];

void precompute()
{
    p_pow[0] = 1;
    for (int i = 1; i < MAX_N; ++i) {
        p_pow[i] = ((p_pow[i-1] % MOD) * (P % MOD)) % MOD;
    }
}

void solve()
{
    string s; cin >> s;
    int n = s.size();

    ll hash = 0;
    for (int i = 0; i < n; ++i) {
        hash = ((hash % MOD) + (((s[i] - 'a' + 1) * p_pow[i]) % MOD)) % MOD;
    }

    // remove character at pos like so
    // asdasd
    // asd sd
    int pos; cin >> pos;
    hash = (MOD + hash - ((s[pos] - 'a' + 1) * p_pow[pos]) % MOD) % MOD;
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
