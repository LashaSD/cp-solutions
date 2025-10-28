#include <iostream>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <map>

using namespace std;
using ll = long long;

#define int ll

// 2113D: Cheater
void solve()
{
    int n; cin >> n;
    vector<int> a(n), b(n);
    for (int& x: a)
        cin >> x;

    for (int& x: b)
        cin >> x;

    set<int> st_l, st_r;
    for (int x: a)
        st_l.insert(x);

    int mn = b[0];
    for (int i = 0; i < n; ++i) {
        mn = min(mn, b[i]);

        if (*st_l.begin() > mn) {
            cout << n - i << '\n';
            return;
        } else if ((st_l.size() == 1) || (st_l.size() > 1 && *(++st_l.begin()) > mn)) {
            auto it = st_r.upper_bound(mn);
            if (it != st_r.end()) {
                cout << n - i << '\n';
                return;
            }
        }

        st_l.erase(a[n - 1 - i]);
        st_r.insert(a[n - 1 - i]);
    }

    cout << 0 << '\n';
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
