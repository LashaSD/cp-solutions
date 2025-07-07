#include <bits/stdc++.h>
#include <filesystem>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

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

struct Str {
    string& s;
    ll hash;
};

// 1840E: Character Blocking
void solve()
{
    string s1, s2;
    cin >> s1 >> s2;
    int n = s1.size();

    ll hash_1 = 0, hash_2 = 0;
    for (int i = 0; i < n; ++i) {
        hash_1 = ((hash_1 % MOD) + (((s1[i] - 'a' + 1) * p_pow[i]) % MOD)) % MOD;
    }

    for (int i = 0; i < n; ++i) {
        hash_2 = ((hash_2 % MOD) + (((s2[i] - 'a' + 1) * p_pow[i]) % MOD)) % MOD;
    }

    Str str1 = {.s = s1}, str2 = {.s = s2};
    str1.hash = hash_1;
    str2.hash = hash_2;

    auto swp = [&](Str& s1, Str& s2, int pos1, int pos2) {
        pos1--;
        pos2--;

        char c1 = s1.s[pos1];
        char c2 = s2.s[pos2];

        s1.hash = (MOD + s1.hash - ((c1 - 'a' + 1) * p_pow[pos1]) % MOD) % MOD;
        s1.hash = ((s1.hash % MOD) + (((c2 - 'a' + 1) * p_pow[pos1]) % MOD) % MOD) % MOD;

        s2.hash = (MOD + s2.hash - ((c2 - 'a' + 1) * p_pow[pos2]) % MOD) % MOD;
        s2.hash = ((s2.hash % MOD) + (((c1 - 'a' + 1) * p_pow[pos2]) % MOD) % MOD) % MOD;

        swap(s1.s[pos1], s2.s[pos2]);
    };

    int t, q;
    cin >> t >> q;
    vector<int> blocked_at(q, -1);
    for (int i = 0; i < q; ++i) {
        // process unblocked characters
        if (i >= t && blocked_at[i-t] != -1) {
            int pos = blocked_at[i-t];
            char c1 = str1.s[pos], c2 = str2.s[pos];

            str1.hash = ((str1.hash % MOD) + (((c1 - 'a' + 1) * p_pow[pos]) % MOD) % MOD) % MOD;
            str2.hash = ((str2.hash % MOD) + (((c2 - 'a' + 1) * p_pow[pos]) % MOD) % MOD) % MOD;
            dbg("UNBLOCK", pos);
        }

        int q_t; cin >> q_t;

        if (q_t == 1) {
            int pos; cin >> pos;
            // block character
            pos--;
            blocked_at[i] = pos;

            char c1 = str1.s[pos], c2 = str2.s[pos];

            str1.hash = (MOD + str1.hash - ((c1 - 'a' + 1) * p_pow[pos]) % MOD) % MOD;
            str2.hash = (MOD + str2.hash - ((c2 - 'a' + 1) * p_pow[pos]) % MOD) % MOD;
            dbg("BLOCK", pos);

            dbg(str1.hash);
            dbg(str2.hash);
        } else if (q_t == 2) {
            int id1, pos1, id2, pos2;
            cin >> id1 >> pos1 >> id2 >> pos2;
            Str& loc_str1 = id1 == 1 ? str1 : str2;
            Str& loc_str2 = id2 == 1 ? str1 : str2;
            swp(loc_str1, loc_str2, pos1, pos2);
        } else if (q_t == 3) {
            if (str1.hash == str2.hash) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
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
