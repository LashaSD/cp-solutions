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

const int p = 1e9 + 6967;

// 2085D: Serval and Kaitenzushi Buffet
void solve()
{
    int n, k;
    cin >> n >> k;

    vector<int> d(n);
    for (int i = 0; i < n; ++i) {
        cin >> d[i];
    }

    int x = n / (k + 1);
    vector<int> bounds;
    for (int i = n % (k + 1); i < n; i += (k + 1)) {
        bounds.push_back(i);
    }

    multiset<int> st;
    int j = 0;
    int ans = 0;
    for (int i = 0; i < 10; ++i) {
        int l = bounds[i];
        while (j <= l) {
            st.insert(d[j]);
            j++;
        }

        auto mx = --st.end();
        ans += *mx;
        st.erase(mx);
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
