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

// GYM106144M: Tactical Game
void solve()
{
    int n; cin >> n;
    string s; cin >> s;
    n = s.size();

    int sum = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '1')
            sum++;
    }

    int current = 0, mx = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '1') {
            current++;
            mx = max(mx, current);
        } else {
            current = 0;
        }
    }

    mx = min(3ll, mx);
    sum -= max(0ll, mx - 1);

    cout << sum << '\n';
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
