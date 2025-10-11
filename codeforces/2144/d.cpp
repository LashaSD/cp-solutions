#include <iostream>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;
using ll = long long;

#define int ll

const int maxN = 4e5;

// 2144D: Price Tags
void solve()
{
    int n, y; 
    cin >> n >> y;

    vector<int> vec(n);

    int m = -1;
    vector<int> cnt(maxN + 1);
    for (int& x: vec) {
        cin >> x;
        m = max(x, m);
        cnt[x]++;
    }

    vector<int> cnt_pref(maxN + 1);
    for (int i = 1; i <= maxN; ++i) {
        cnt_pref[i] = cnt_pref[i-1] + cnt[i];
    }

    int ans = LLONG_MIN;

    for (int x = 2; x <= max(2ll, m); ++x) {
        int cost = 0;
        int sum = 0;
        for (int i = 1; i <= (m + x - 1) / x; ++i) {
            int l = (i - 1) * x + 1;
            int r = min(maxN, i * x);

            if (l > r) {
                continue;
            }

            int loccnt = cnt_pref[r] - cnt_pref[l - 1];

            if (loccnt == 0) {
                continue;
            }

            sum += i * loccnt;
            cost += y * max(0ll, (loccnt - cnt[i]));
        }

        //cerr << "COST: " << cost << '\n';
        ans = max(ans, sum - cost);
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
