#include <climits>
#include <functional>
#include <set>
#include <cstdio>
#include <algorithm>
#include <cstdint>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

// D. Creating a Schedule
void solve()
{
    int n, m;
    scanf("%d %d", &n, &m);
    // { floor, value }
    vector<pair<int, int>> vec(m);
    for (int i = 0; i < m; ++i) {
        int num;
        scanf("%d", &num);

        vec[i].first = num / 100;
        vec[i].second = num;
    }

    sort(vec.begin(), vec.end());
    vector<pair<int, int>> low(n), high(n);
    int l = 0, r = m-1;
    for (int i = 0; i < n; ++i, ++l, --r) {
        if (i + 1 < n) {
            low[i] = vec[l];
            high[i] = vec[r];
            low[i+1] = vec[r];
            high[i+1] = vec[l];
            ++i;
        } else {
            low[i] = vec[l];
            high[i] = vec[r];
        }
    }

    for (int i = 0; i < n; ++i) {
        printf("%d %d ", low[i].second, high[i].second);
        printf("%d %d ", low[i].second, high[i].second);
        printf("%d %d\n", low[i].second, high[i].second);
    }
}

int T = 1;
int32_t main(void)
{
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    scanf("%d", &T);
    while(T--)
        solve();
    return 0;
}
