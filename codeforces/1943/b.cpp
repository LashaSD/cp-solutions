#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

const int maxN = 2e5 + 5;
const int mod = 1e9 + 6967;
const int p = 31;
vector<int> p_pow(maxN + 1);
vector<int> odds(maxN + 1), evens(maxN + 1);
string s;

void precompute()
{
    p_pow[0] = 1;
    for (int i = 1; i <= maxN; ++i) {
        p_pow[i] = (p_pow[i-1] * p) % mod;
    }

    odds[1] = p_pow[1];
    for (int i = 2; i <= maxN; ++i) {
        if (i % 2 == 1)
            odds[i] = (odds[i-2] + p_pow[i]) % mod;
        else
            odds[i] = odds[i-1];
    }

    for (int i = 2; i <= maxN; ++i) {
        if (i % 2 == 0)
            evens[i] = (evens[i-2] + p_pow[i]) % mod;
        else
            evens[i] = evens[i-1];
    }
}

bool compare(vector<int>& h1, vector<int>& h2, int l1, int r1, int l2, int r2)
{
    int hv1, hv2;
    if (l1 < l2) {
        int dx = l2 - l1;
        hv1 = p_pow[dx] * ((mod + (h1[r1] - h1[l1])) % mod) % mod;
        hv2 = (mod + (h2[r2] - h2[l2])) % mod;
    } else {
        int dx = l1 - l2;
        hv1 = (mod + (h1[r1] - h1[l1])) % mod;
        hv2 = p_pow[dx] * ((mod + (h2[r2] - h2[l2])) % mod) % mod;
    }

    return hv1 == hv2;
}

bool has_pattern(vector<int>& h1, int l, int r)
{
    int k = r - l + 1;
    char a = s[l], b = s[l+1];
    if (a == b) return false;
    int h = ((odds[k] * (a - 'a' + 1)) % mod + (evens[k] * (b - 'a' + 1)) % mod) % mod;
    h = (p_pow[l - 1] * h) % mod;
    int hv = (mod + (h1[r] - h1[l-1])) % mod;
    return h == hv;
}

// 1943B: Non-Palindromic Substring
void solve()
{
    int n, q;
    cin >> n >> q;
    cin >> s;
    s.insert(0, " ");
    vector<int> h1(n+1), h2(n+1);
    for (int i = 1; i <= n; ++i) {
        h1[i] = (h1[i-1] + ((s[i] - 'a' + 1) * p_pow[i]) % mod) % mod;
    }

    for (int i = n; i >= 1; --i) {
        int idx = n - i + 1;
        h2[idx] = (h2[idx-1] + ((s[i] - 'a' + 1) * p_pow[idx]) % mod) % mod;
    }

    auto is_palindrome = [&](int l, int r) {
        return compare(h1, h2, l, r, n-r+1, n-l+1);
    };
    
    for (int qq = 0; qq < q; ++qq) {
        int l, r;
        cin >> l >> r;

        if (has_pattern(h1, l, r)) {
            // sum up only evens
            int k = r - l + 1;
            ll sum = (k/2)*(k/2 + 1);
            cout << sum << '\n';
            continue;
        } else if (is_palindrome(l, r)) {
            if (is_palindrome(l+1, r) && is_palindrome(l, r-1)) {
                // only one distinct character
                cout << 0 << '\n';
                continue;
            }

            if (!is_palindrome(l+1, r)) {
                l++;
            } else {
                r--;
            }
        }

        int k = r - l + 1;
        ll sum = (2 + k) * (k - 1) / 2;
        cout << sum << '\n';
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
