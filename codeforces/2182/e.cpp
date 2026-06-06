#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <cstdint>
#include <set>
#include <algorithm>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2182E: New Year's Gifts
void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(m);
    for (int i = 0; i < m; ++i) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());

    vector<pair<int, int>> vec(n);
    for (int i = 0; i < n; ++i) {
        int x, y, z;
        cin >> x >> y >> z;
        k -= y;
        vec[i].xx = x;
        vec[i].yy = z - y;
    }

    sort(vec.begin(), vec.end());

    int ans = 0;
    vector<bool> marked(n);
    int it = 0;
    set<pair<int, int>> st;
    for (int i = 0; i < m; ++i) {
        // query:
        // highest y, out of all that have x <= a[i]
        while (it < n && vec[it].xx <= a[i]) {
            st.insert({vec[it].yy, it});
            it++;
        }

        if (st.size() == 0) continue;
        auto highest = *(--st.end());
        marked[highest.yy] = 1;
        st.erase(--st.end());
        ans++;
    }

    vector<int> rest;
    for (int i = 0; i < n; ++i) {
        if (!marked[i]) {
            rest.push_back(vec[i].yy);
        }
    }

    sort(rest.begin(), rest.end());

    for (int x: rest) {
        if (k < x) break;
        k -= x;
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
