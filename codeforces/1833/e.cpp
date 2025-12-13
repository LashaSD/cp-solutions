#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 1833E: Round Dance
void solve()
{
    int n; cin >> n;
    vector<int> a(n+1), d(n+1, 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        d[a[i]]++;
    }

    vector<int> p(n+1), s(n+1, 1);
    vector<bool> ok(n+1);
    for (int i = 1; i <= n; ++i) 
        p[i] = i;

    for (int i = 1; i <= n; ++i) {
        ok[i] = d[i] == 1;
    }

    auto head = [&](auto self, int u) {
        if (p[u] == u) return u;
        return p[u] = self(self, p[u]);
    };

    auto join = [&](int u, int v) {
        int hu = head(head, u);
        int hv = head(head, v);
        if (hu == hv) return;
        p[hu] = p[hv];
        s[hv] += s[hu];
        ok[hv] = ok[hv] || ok[hu];
    };

    for (int i = 1; i <= n; ++i) {
        int x = a[i];
        join(x, i);
    }

    int mx = 0;
    int open = 0, close = 0;
    for (int i = 1; i <= n; ++i) {
        if (head(head, i) == i) {
            mx++;

            if (ok[i] || s[i] == 2) {
                open++;
            } else {
                close++;
            }
        }
    }

    cout << close + (open>0) << ' ' << mx << '\n';
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
