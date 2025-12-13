#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 1641B: Repetitions Decoding
void solve()
{
    int n; cin >> n;
    vector<int> a(n);
    list<int> lst;
    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        lst.push_back(x);
    }

    using P = pair<int, int>;
    vector<P> ops;
    vector<int> ans;
    int pi = 0;
    for (auto i = lst.begin(); i != lst.end(); ) {
        int x = *i;
        auto r = next(i, 1);
        int pr = pi + 1;
        while (r != lst.end()) {
            if (*r == x) break;
            r++;
            pr++;
        }

        if (r == lst.end()) {
            cout << -1 << '\n';
            return;
        }

        int pj1 = pi, pj2 = pr;
        auto j1 = i, j2 = r;
        while (j1 != r) {
            if (j2 != lst.end() && *j1 == *j2) {
                pj1++, pj2++;
                j1++, j2++;
                continue;
            }

            if (ops.size() >= 2*n*n) {
                cout << -1 << '\n';
                return;
            }

            ops.push_back({pj2, *j1});
            j2 = lst.insert(j2, *j1);
            j2 = lst.insert(j2, *j1);

            pj1++, pj2++;
            j1++, j2++;
        }

        ans.push_back(pj2 - pi);
        if (j2 == lst.end()) break;
        i = j2;
        pi = pj2;
    }

    cout << ops.size() << '\n';
    for (auto [p, c]: ops) {
        cout << p << ' ' << c << '\n';
    }
    cout << ans.size() << '\n';
    for (int x: ans) {
        cout << x << ' ';
    }
    cout << '\n';
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
