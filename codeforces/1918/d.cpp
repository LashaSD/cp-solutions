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
vector<int> vec;
vector<int> pref;
int n;

bool ok(int x)
{
    vector<int> dp(n+1);
    multiset<int> s;
    s.insert(0);

    int l = 0;
    dp[1] = vec[1];
    s.insert(dp[1]);
    for (int i = 2; i <= n; ++i) {
        while (pref[i-1] - pref[l] > x) {
            s.erase(s.find(dp[l]));
            l++;
        }

        dp[i] = *s.begin() + vec[i];
        s.insert(dp[i]);
    }

    for (int i = n; i >= 1; --i) {
        if (pref[n] - pref[i] > x) break;

        if (dp[i] <= x) 
            return true;
    }

    return false;
}

// 1918D: Blocking Elements
void solve()
{
    cin >> n;
    vec.resize(n+1);
    ll sum = 0;
    for (int i = 1; i <= n; ++i) {
        int x; cin >> x;
        vec[i] = x;
        sum += x;
    }

    pref.resize(n+1);
    for (int i = 1; i <= n; ++i) {
        pref[i] = pref[i-1] + vec[i];
    }

    int l = 1, r = sum;
    int ans = -1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (ok(mid)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
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
