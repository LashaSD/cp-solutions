#include <bits/stdc++.h>

using namespace std;
using ll = long long;

vector<pair<ll, ll>> read_input()
{
    string s; cin >> s;
    int n = s.size();

    vector<pair<ll, ll>> vec;
    int i = 0, j = 0;
    while (j < n) {
        // move j to next -
        while (j < n && s[j] != '-') j++;
        ll l = stoll(string(s.begin() + i, s.begin() + j));
        i = j + 1;
        // move j to ,
        while (j < n && s[j] != ',') j++;
        ll r = stoll(string(s.begin() + i, s.begin() + j));
        vec.push_back(make_pair(l, r));
        i = j + 1;
    }

    return vec;
}

vector<int> buf(1024);
static bool is_invalid(ll x)
{
    buf.clear();
    while (x > 0) {
        buf.push_back(x % 10);
        x /= 10;
    }

    reverse(buf.begin(), buf.end());
    int n = buf.size();
    for (int k = 1; k <= n/2; ++k) {
        if (n % k != 0) continue;
        bool ok = 1;
        for (int i = 0; i < n; ++i) {
            if (buf[i] != buf[i % k]) {
                ok = 0;
                break;
            }
        }

        if (ok) return true;
    }

    return false;
}

ll sum(ll l, ll r)
{
    if (r < l) swap(l, r);
    ll ans = 0;
    for (ll x = l; x <= r; ++x) {
        if (is_invalid(x)) {
            ans += x;
        }
    }

    return ans;
}

signed main()
{
    auto vec = read_input();
    ll ans = 0;
    for (auto [l, r]: vec) {
        ans += sum(l, r);
    }

    cout << ans << '\n';
}
