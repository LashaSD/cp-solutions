#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

const int p = 31;
const int mod = 1e9 + 6967;

const int maxN = 1e6 + 5;
ll p_pow[maxN + 1];

void precompute()
{
    p_pow[0] = 1;
    for (int i = 1; i <= maxN; ++i) {
        p_pow[i] = (p_pow[i-1] * p) % mod;
    }
}

static inline bool compare(vector<int>& h1, vector<int>& h2, int l1, int r1, int l2, int r2)
{
    if (l1 > l2) {
        swap(l1, l2);
        swap(r1, r2);
        swap(h1, h2);
    }

    int dx = l2 - l1;
    int v1 = ((mod + (h1[r1] - h1[l1-1])) % mod) * p_pow[dx] % mod;
    int v2 = (mod + (h2[r2] - h2[l2-1])) % mod;

    return v1 == v2;
}

// 1951E: No Palindromes
void solve()
{
    string s; cin >> s;
    int n = s.size();
    s.insert(0, " ");

    vector<int> h1(n+1), h2(n+2);
    for (int i = 1; i <= n; ++i) {
        h1[i] = (p_pow[i] * (s[i]-'a'+ 1)) % mod;
        h1[i] = (h1[i] + h1[i-1]) % mod;
    }

    for (int i = n; i >= 1; --i) {
        int idx = n - i + 1;
        h2[idx] = (p_pow[idx] * (s[i]-'a'+1)) % mod;
        h2[idx] = (h2[idx] + h2[idx-1]) % mod;
    }

    auto is_palindrome = [&](int l, int r)
    {
        return compare(h1, h2, l, r, n-r+1, n-l+1);
    };

    if (!is_palindrome(1, n)) {
        cout << "YES\n1\n";
        cout << string(s.begin()+1, s.end()) << '\n';
        return;
    }

    for (int i = 1; i <= n-1; ++i) {
        if (!is_palindrome(1, i) && !is_palindrome(i+1, n)) {
            string s1(s.begin() + 1, s.begin() + i+1);
            string s2(s.begin() + i+1, s.end());
            cout << "YES\n2\n";
            cout << s1 << ' ' << s2 << '\n';
            return;
        }
    }

    cout << "NO\n";
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
