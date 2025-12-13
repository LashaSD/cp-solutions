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

// 2042D: Recommendations
void solve()
{
    int n; cin >> n;
    vector<pair<int, int>> vec(n);
    for (int i = 0; i < n; ++i) {
        cin >> vec[i].xx >> vec[i].yy;
    }

    vector<int> id(n);
    for (int i = 0; i < n; ++i) {
        id[i] = i;
    }

    sort(id.begin(), id.end(), [&](int a, int b) {
        return vec[a] < vec[b];
    });

    set<int> rs;
    vector<pair<int, int>> st;
    vector<int> ans(n);
    for (int i = 0; i < n; ++i) {
        auto [l0, r0] = vec[id[i]];
        
        // check if another l0 exists
        bool dup = false;
        int maxl, minr = -1;
        if (i < n-1 && vec[id[i+1]].xx == l0) {
            minr = vec[id[i+1]].yy;
            dup = 1;
        }

        while (!st.empty() && st.back().yy < r0) {
            st.pop_back();
        }

        if (dup) {
            maxl = l0;
        } else {
            if (st.empty()) {
                st.push_back({l0, r0});
                rs.insert(r0);
                continue;
            }

            maxl = st.back().xx;
        }

        st.push_back({l0, r0});
        auto it = rs.lower_bound(r0);
        if (it != rs.end()) {
            if (minr == -1)
                minr = *it;
            else
                minr = min(minr, *it);
        }

        rs.insert(r0);

        if (minr != -1) {
            ans[id[i]] = (minr - maxl + 1) - (r0 - l0 + 1);
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << ans[i] << '\n';
    }
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
