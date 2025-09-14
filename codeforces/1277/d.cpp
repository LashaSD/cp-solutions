#include <bits/stdc++.h>

using namespace std;
using ll = long long;
//#define int ll

const int P = 31;
const int MAX_N = 4e6 + 1;
const int MOD = 1e9 + 9;
int p_pow[MAX_N] = {0};

void precompute()
{
    ll pow = 1;
    for (int i = 0; i <= MAX_N; ++i) {
        p_pow[i] = pow;
        pow = (pow * (ll) P) % MOD;
    }
}

// 1277D: Let's Play the Words? 
void solve()
{
    int n; cin >> n;
    map<ll, int> oc;
    vector<string> vec(n);
    for (int k = 0; k < n; ++k) {
        cin >> vec[k];
        string& s = vec[k];
        ll hash = 0;
        for (int i = 0; i < (int) s.size(); ++i) {
            char c = s[i];
            hash += ((ll)(c - '0' + 1) * (ll)p_pow[i]) % MOD;
            hash %= MOD;
        }

        oc[hash]++;
    }

    // 0 -> 0 - 1
    // 1 -> 1 - 0
    // 2 -> 0 - 0
    // 3 -> 1 - 1
    vector<vector<int>> f(4);

    int f_01 = 0;
    int f_10 = 0;
    int f_11 = 0;
    int f_00 = 0;

    for (int k = 0; k < n; ++k) {
        string& s = vec[k];
        ll suff_hash = 0;
        ll pref_hash = 0;
        for (int i = 0; i < (int) s.size(); ++i) {
            char c = s[i];
            int pow = s.size() - 1 - i;

            suff_hash += ((ll)(c - '0' + 1) * (ll)p_pow[pow]) % MOD;
            suff_hash %= MOD;

            pref_hash += ((ll)(c - '0' + 1) * (ll)p_pow[i]) % MOD;
            pref_hash %= MOD;
        }

        int freaky = 0;
        if (pref_hash == suff_hash) freaky++;

        if (oc[suff_hash] == freaky) {
            if (s.front() == '0' && s.back() == '1')
                f[0].push_back(k);
            else if (s.front() == '1' && s.back() == '0')
                f[1].push_back(k);
            else if (s.front() == '0' && s.back() == '0')
                f[2].push_back(k);
            else if (s.front() == '1' && s.back() == '1')
                f[3].push_back(k);
        }

        if (s.front() == '0' && s.back() == '1')
            f_01++;
        else if (s.front() == '1' && s.back() == '0')
            f_10++;
        else if (s.front() == '0' && s.back() == '0')
            f_00++;
        else if (s.front() == '1' && s.back() == '1')
            f_11++;
    }

    int cnt = min(f_01, f_10);
    int k = max(f_01, f_10) - cnt;
    int cost = k / 2;

    if (f_01 > 0 || f_10 > 0) {
        vector<int> f_vec;
        if (f_01 > f_10) {
            f_vec = move(f[0]);
        } else {
            f_vec = move(f[1]);
        }

        if ((int) f_vec.size() < cost) {
            cout << -1 << '\n';
            return;
        }

        cout << cost << '\n';
        for (int i = 0; i < cost; ++i) 
            cout << f_vec[i] + 1 << ' ';
        cout << '\n';
    } else {
        if (f_00 > 0 && f_11 > 0) {
            cout << -1 << '\n';
        } else {
            cout << 0 << "\n\n";
        }
    }
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
