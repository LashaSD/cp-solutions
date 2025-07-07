#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

// 1609D: Social Network
void solve()
{
    int n, d;
    cin >> n >> d;
    vector<int> p(n+1), s(n+1);

    auto reset_dsu = [&]() {
        for (int i = 1; i <= n; ++i) {
            p[i] = i;
            s[i] = 1;
        }
    };

    function<int(int)> head = [&](int u) {
        if (p[u] == u)
            return u;
        return p[u] = head(p[u]);
    };

    auto merge = [&](int u, int v) -> bool {
        int h1 = head(u);
        int h2 = head(v);
        if (h1 != h2) {
            p[h2] = h1;
            s[h1] += s[h2];
            return true;
        }
        return false;
    };

    vector<pair<int, int>> reqs(d);
    for (int i = 0; i < d; ++i) {
        int u, v;
        cin >> u >> v;
        reqs[i] = {u, v};
    }

    for (int k = 0; k < d; ++k) {
        reset_dsu();
        int bonus = 0;
        for (int i = 0; i <= k; ++i) {
            pair<int, int>& edge = reqs[i];
            if(!merge(edge.first, edge.second)) {
                bonus++;
            }
        }

        set<pair<int, int>> heads;

        for (int i = 1; i <= n; ++i) {
            int h = head(i);
            heads.insert({s[h], h});
        }

        while (bonus > 0 && heads.size() >= 2) {
            auto s1 = prev(heads.end(), 1);
            auto s2 = prev(heads.end(), 2);
            int h1 = s1->second;
            int h2 = s2->second;

            merge(h1, h2);

            heads.erase(s1);
            heads.erase(s2);
            bonus--;
            heads.insert({s[h1], h1});
        }

        int mx = 0;
        for (int i = 1; i <= n; ++i)
            mx = max(s[i], mx);

        cout << mx-1 << '\n';
    }
}

int T = 1;
int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // cin >> T;
    while(T--)
        solve();
    return 0;
}
