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
#define xx first
#define yy second

// 1061D: TV Shows
void solve()
{
    int n, x, y;
    cin >> n >> x >> y;
    vector<pair<int, int>> vec(n);
    for (int i = 0; i < n; ++i) {
        cin >> vec[i].xx >> vec[i].yy;
    }

    sort(vec.begin(), vec.end());

    vector<pair<int, int>> tv;
    tv.reserve(n);

    set<pair<int, int>> st;
    for (auto [l, r]: vec) {
        if (st.size() > 0) {
            auto it = st.lower_bound({l, 0});
            if (it != st.begin() && --it != st.end() && it->first < l) {
                int i = it->second;
                int dx = l - it->first;
                if (dx*y <= x) {
                    tv[i].second = r;
                    st.erase(it);
                    st.insert({r, i});
                    continue;
                }
            }
        }

        tv.push_back({l, r});
        st.insert({r, tv.size() - 1});
    }

    const int mod = 1e9 + 7;
    int ans = 0;
    for (auto [l, r]: tv) {
        ans = (ans + (x + (y*(r - l) % mod)) % mod) % mod;
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
