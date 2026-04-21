#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2201A2: Lost Civilization (Hard Version)
void solve()
{
    int n; cin >> n;
    vector<int> vec(n);
    for (int i = 0; i < n; ++i) {
        cin >> vec[i];
    }

    map<int, int> last_oc;
    last_oc[vec[0]] = 1;

    map<int, vector<int>> mp;
    int a = 0;
    ll current = 1, sum = 1;
    for (int i = 1; i < n; ++i) {
        bool depends = 1;
        if (vec[i] - vec[i-1] > 1) {
            current++;
            a = i;
            depends = 0;
        }

        if (vec[i] <= vec[i-1] && vec[i] <= vec[a]) {
            current++;
            a = i;
            depends = 0;
        }

        if (depends) {
            mp[last_oc[vec[i]-1]].push_back(i+1);
        }

        sum += current;
        last_oc[vec[i]] = i+1;
    }

    ll ans = sum;
    // cerr << 0 << ' ' << sum << '\n';
    for (int i = 0; i < n-1; ++i) {
        // transition from i to i+1

        sum -= n - i;
        for (int j: mp[i+1]) {
            sum += n-j+1;
        }
        ans += sum;
        // cerr << i+1 << ' ' << sum << '\n';
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
