#include <iostream>
#include <cassert>
#include <climits>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <map>

using namespace std;
using ll = long long;

#define int ll

const int p1 = 31;
const int m1 = 1000001801;

const int p2 = 137;
const int m2 = 998'244'353;

const int maxN = 2e5 + 5;
vector<int> p1_pow(maxN);
vector<int> p2_pow(maxN);

void precompute()
{
    p1_pow[0] = 1;
    for (int i = 1; i < maxN; ++i) {
        p1_pow[i] = p1_pow[i-1] * p1 % m1;
    }

    p2_pow[0] = 1;
    for (int i = 1; i < maxN; ++i) {
        p2_pow[i] = p2_pow[i-1] * p2 % m2;
    }
}

void comp_hash(vector<int>& out, const string& s, const vector<int>& p_pow, const int m)
{
    int n = s.size();
    for (int i = 1; i <= n; ++i) {
        out[i] = (out[i-1] + ((s[i-1] - 'a' + 1) * p_pow[i - 1]) % m) % m;
    }
}

bool cmp(const vector<int>& hash, int l, int l1, int len, const vector<int>& p_pow, int m)
{
    int n = hash.size() - 1;
    if (l > l1)
        swap(l, l1);

    if (l1 + len - 1 >= n) return false;

    int diff = l1 - l;
    int h1 = (m + hash[l + len] - hash[l]) % m;
    int h2 = (m + hash[l1 + len] - hash[l1]) % m;
    h1 = (h1 * p_pow[diff]) % m;

    return h1 == h2;
}

// 1984D: "a" String Problem
void solve()
{
    string s;
    cin >> s;
    int n = (int) s.size();

    vector<int> closest(n);
    closest[n-1] = s.back() == 'a' ? -1 : n-1;
    for (int i = n-2; i >= 0; --i) {
        if (s[i] != 'a') {
            closest[i] = i;
        } else {
            closest[i] = closest[i+1];
        }
    }

    if (closest[0] == -1) {
        cout << n-1 << '\n';
        return;
    }

    vector<int> hash1(n+1);
    vector<int> hash2(n+1);
    comp_hash(hash1, s, p1_pow, m1);
    comp_hash(hash2, s, p2_pow, m2);

    int l = closest[0];
    int ans = 0;
    for (int r = l; r < n; ++r) {
        int len = r - l + 1;
        int i = r+1;
        int c = l;
        bool ok = true;
        while (i < n) {
            int nxt = closest[i];
            if (nxt == -1) break;

            int as = nxt - i;

            if (!(cmp(hash1, l, nxt, len, p1_pow, m1))) 
            {
                ok = false;
                break;
            }

            i = nxt + len;
            c = min(c, as);
        }

        if (ok) {
            // cerr << "OK: " << l << ' ' << r << '\n';
            ans += c + 1;
        }
    }

    cout << ans << '\n';
}

int T = 1;
int32_t main(void)
{
    precompute();
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while(T--)
        solve();

    return 0;
}
