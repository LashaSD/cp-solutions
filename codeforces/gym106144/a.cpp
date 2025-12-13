#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll

// GYM106144A: Delete the Array
void solve()
{
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    set<pair<int, int>> st, sti;

    for (int i = 0; i < n; ++i) {
        st.insert({a[i], i});
        sti.insert({i, a[i]});
    }

    auto remove = [&](int x, int i) {
        st.erase({x, i});
        sti.erase({i, x});
    };

    int ans = 0;
    while (st.size() > 0) {
        if (st.size() == 1) {
            ans++;
            break;
        }

        auto l1 = sti.begin();
        auto l2 = ++sti.begin();
        if (l1->second == l2->second) {
            remove(l1->second, l1->first);
            remove(l2->second, l2->first);
            ans++;
            continue;
        }

        auto it = st.begin();
        remove(it->first, it->second);
        ans++;
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
