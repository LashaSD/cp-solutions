#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll

static const int MOD = 1e9 + 7;
static const int MAX_N = 2e6 + 1;

ll binpow(ll a, ll b) 
{
    ll res = 1;
    a = a % MOD;
    while (b > 0){
        if ((b & 1) != 0){
            res = (res * a) % MOD;
        }

        a = (a * a) % MOD;
        b >>= 1LL;
    }
    return res;
}

// 2035D: Yet Another Real Number Problem
void solve()
{
    int n; cin >> n;
    vector<int> vec(n);
    for (int& x: vec)
        cin >> x;

    vector<int> m(n+1), pref_two(n+1);
    for (int i = 1; i <= n; ++i) {
        int x = vec[i-1];

        int shift = 63 - __builtin_clzll(x & -x);
        m[i] = m[i-1] + (x >> shift);
        pref_two[i] = pref_two[i-1] + shift;
    }

    // {count of even numbers, l, index}
    stack<pair<int, pair<int, int>>> st;
    int ans = 0;
    vector<int> out(n);
    for (int i = 1; i <= n; ++i) {
        int x = vec[i-1];
        int x_k = 0;
        int x_l = i-1;
        int x_i = i-1;
        bool trigger = false;

        ans = (ans + x) % MOD;

        while (!st.empty()) {
            auto top = st.top();
            int y_l = top.second.first;
            int y_i = top.second.second;
            int y = vec[y_i];
            int y_k = top.first;
            int y_pow = 63 - __builtin_clzll(y & -y);

            bool ok_to_merge = false;
            if (x_k + y_pow >= 31) ok_to_merge = true;
            else {
                int x_num = x * (1ll << (x_k + y_pow));

                if (y <= x_num) {
                    ok_to_merge = true;
                }
            }

            if (!ok_to_merge) break;

            int k = y_k + y_pow + x_k;

            int old_y = (y * binpow(2, y_k)) % MOD;
            old_y = (old_y + (m[y_i] - m[y_l]) % MOD) % MOD;

            int old_x = x;
            if (trigger) {
                old_x = 0;
                old_x = (old_x + (x * binpow(2, x_k)) % MOD) % MOD;
                old_x = (old_x + (m[x_i] - m[x_l]) % MOD) % MOD;
            }

            int old = (old_x + old_y) % MOD;

            int nw = (x * binpow(2, k)) % MOD;
            nw = (nw + (m[x_i] - m[y_l]) % MOD) % MOD;

            ans = (MOD + (ans - old)) % MOD;
            ans = (ans + nw) % MOD;

            x_k = k;
            x_l = y_l;

            st.pop();
            trigger = true;
        }

        st.push({x_k, {x_l, x_i}});
        out[i-1] = ans;
    }

    for (int x: out)
        cout << x << ' ';
    cout << '\n';
}

int T = 1;
int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while(T--)
        solve();
    return 0;
}
