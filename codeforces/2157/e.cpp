#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <cstdint>
#include <set>
#include <algorithm>
#include <functional>
#include <map>

#define assert(v) do { if (!(v)) { *(int*)0 = 0; } } while (0)

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2157E: Adjusting Drones
void solve()
{
    int n, k;
    cin >> n >> k;

    vector<int> vec(n);
    int mx = 0;
    vector<int> f(2*n+5);
    for (int i = 0; i < n; ++i) {
        cin >> vec[i];
        mx = max(mx, vec[i]);
        f[vec[i]]++;
    }

    vector<int> st;
    st.push_back(mx+1);
    int ans = 0;
    for (int x = mx; x >= 1; --x) {
        if (f[x] == 0) {
            st.push_back(x);
            continue;
        }

        int d = k - f[x];
        int pos = x;
        while (f[x] > 1) {
            pos = st.back();
            st.pop_back();
            if (st.size() == 0) {
                st.push_back(pos+1);
            }
            f[x]--;

            if (f[x] == k) {
                ans = max(ans, pos - x);
            }
        }
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


