#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <cstdint>
#include <set>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2184E: Exquisite Array
void solve()
{
    int n; cin >> n;
    vector<int> vec(n+1);
    for (int i = 1; i <= n; ++i) {
        cin >> vec[i];
    }

    vector<vector<int>> breaks(n+1);
    for (int i = 1; i <= n-1; ++i) {
        int d = abs(vec[i+1] - vec[i]);
        breaks[d+1].push_back(i);
    }

    set<int> walls;
    walls.insert(0);
    walls.insert(n);
    int ans = n*(n - 1) / 2;
    cout << ans << ' ';
    for (int k = 2; k < n; ++k) {
        for (int pos: breaks[k]) {
            int l = *(--walls.lower_bound(pos));
            int r = *walls.upper_bound(pos);
            int len = r - l;
            ans -= len * (len - 1) / 2;
            int l1 = pos - l;
            if (l1 >= 2) {
                ans += l1*(l1 - 1) / 2;
            }

            int l2 = r - pos;
            if (l2 >= 2) {
                ans += l2*(l2 - 1) / 2;
            }

            walls.insert(pos);
        }

        cout << ans << ' ';
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
