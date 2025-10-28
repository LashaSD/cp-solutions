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

// 2031D: Penchick and Desert Rabbit
void solve()
{
    int n; cin >> n;
    vector<int> vec(n);
    for (int& x: vec)
        cin >> x;

    vector<int> pref(n+1);
    pref[0] = LLONG_MIN;
    for (int i = 1; i <= n; ++i) {
        pref[i] = max(pref[i-1], vec[i-1]);
    }

    vector<int> suff(n+1);
    suff[n] = LLONG_MAX;
    vector<int> ans(n);
    for (int i = n-1; i >= 0; --i) {
        int k = pref[i+1];
        int l = i+1, r = n-1;
        int save = -1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (suff[mid] < k) {
                save = ans[mid];
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }

        ans[i] = max(k, save);
        suff[i] = min(vec[i], suff[i+1]);
    }

    for (int x: ans)
        cout << x << ' ';
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
