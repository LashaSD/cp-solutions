#include <iostream>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;
using ll = long long;

#define int ll

int f(string& s, char c, bool b=1)
{
    int m = s.size();
    int cnt = 0;
    for (int i = 0; i < (m - 1);) {
        if ((s[i] == c && s[i+1] == c) == b) {
            cnt++;
            i += 2;
        } else {
            i++;
        }
    }

    return cnt;
}

// 1804D: Accommodation
void solve()
{
    int n, m;
    cin >> n >> m;
    int ans[2] = {0, 0};

    for (int i = 0; i < n; ++i) {
        string s; cin >> s;
        int ones = count(s.begin(), s.end(), '1');

        int cnt = f(s, '1');
        int mn = ones - min(m / 4, cnt);
        int mx = ones - max(0ll, m / 4 - f(s, '1', 0));

        //cerr << "DBG: " << f(s, '1', 0) << '\n';

        ans[0] += mn;
        ans[1] += mx;
    }

    cout << ans[0] << ' ' << ans[1] << '\n';
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

