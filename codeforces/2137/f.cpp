#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <cstdint>
#include <set>
#include <cstdio>
#include <algorithm>
#include <functional>
#include <map>

#define assert(v) do { if (!(v)) { __builtin_trap(); } } while (0)

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2137F: Prefix Maximum Invariance 
void solve()
{
    int n; cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }

    vector<int> st;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        while (st.size() > 0 && a[st.back()] < a[i]) {
            st.pop_back();
        }

        ll contrib = 0;
        if (a[i] == b[i]) {
            ans += (i+1)*(n - i);
        } else {
            int save = -1;
            int l = 0, r = st.size() - 1;
            while (l <= r) {
                int mid = l + (r - l) / 2;
                if (a[st[mid]] >= b[i]) {
                    l = mid + 1;
                    save = st[mid];
                } else {
                    r = mid - 1;
                }
            }

            if (save != -1) {
                ans += (save+1)*(n - i);
            }
        }

        st.push_back(i);
    }
    cout << ans << '\n';
}

int T = 1;
int32_t main(void)
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    cin >> T;
    while(T--)
        solve();

    return 0;
}
