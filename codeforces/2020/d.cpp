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

struct dsu {
    int n;
    vector<int> p, s;
    dsu(int _n) : n(_n) 
    {
        p.resize(n + 1);
        s.resize(n + 1);
        for (int i = 1; i <= n; ++i) {
            p[i] = i;
            s[i] = 1;
        }
    }

    int head(int u) 
    {
        if (p[u] == u) return u;
        return p[u] = head(p[u]);
    }

    bool join(int u, int v)
    {
        int hu = head(u);
        int hv = head(v);
        if (hu != hv) {
            p[hu] = hv;
            s[hv] += s[hu];

            return true;
        }

        return false;
    }
};

// 2020D: Connect the Dots
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> as(m), ds(m), ks(m);

    for (int i = 0; i < m; ++i) {
        cin >> as[i];
        cin >> ds[i];
        cin >> ks[i];
    }

    vector<dsu> p(11, dsu(n));

    for (int i = 0; i < m; ++i) {
        int a = as[i], d = ds[i];
        int lim = a + d*ks[i];

        int last = a;
        for (; a <= lim;) {
            if (a + d > lim) break;
            last = a;
            a = p[d].head(a + d);
            p[d].join(last, a);
            if (a > lim) break;
        }
    }

    dsu ans(n);
    for (int d = 1; d <= 10; ++d) {
        for (int i = 1; i <= n; ++i) {
            int h = p[d].head(i);
            ans.join(i, h);
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (ans.head(i) == i) ans++;
    }

    cout << ans << '\n';
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
