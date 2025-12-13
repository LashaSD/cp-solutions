#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 1263D: Secret Passwords
void solve()
{
    int n; cin >> n;
    vector<string> vec(n);
    vector<bool> mark(27);
    for (string& s: vec) {
        cin >> s;
        for (const char& c: s) {
            mark[c-'a'] = 1;
        }
    }

    vector<int> p(27);
    for (int i = 0; i < 26; ++i) {
        p[i] = i;
    }

    auto head = [&](auto self, int u) {
        if (p[u] == u) return u;
        return p[u] = self(self, p[u]);
    };

    auto join = [&](int u, int v) {
        int hu = head(head, u);
        int hv = head(head, v);
        p[hu] = hv;
    };

    for (string s: vec) {
        int m = s.size();
        char last_c = s[0];
        for (int i = 1; i < m; ++i) {
            join(last_c - 'a', s[i] - 'a');
        }
    }

    int ans = 0;
    for (int i = 0; i < 26; ++i) {
        if (mark[i] && head(head, i) == i) {
            ans++;
        }
    }

    cout << ans << '\n';
}

int T = 1;
int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //cin >> T;
    while(T--)
        solve();

    return 0;
}
