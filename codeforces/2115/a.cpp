#include <climits>
#include <cstdio>
#include <algorithm>
#include <cstdint>
#include <queue>
#include <vector>
#include <queue>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

// A. Gellyfish and Flaming Peony
void solve()
{
    int n;
    scanf("%d", &n);

    vector<int> vec(n);
    vector<bool> mark(n);
    vector<int> freaky(5001);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &vec[i]);
        mark[i] = 1;
        freaky[vec[i]]++;
    }

    vector<int> dp(5001, 10000);
    for (int i = 0; i < n; ++i)
        dp[vec[i]] = 0;

    for (int x = *max_element(vec.begin(), vec.end()); x >= 1; --x) {
        for (int i = 0; i < n; ++i) {
            // x is gcd of a combination of different elements in vec
            int g = __gcd(x, vec[i]);
            dp[g] = min(dp[g], dp[x] + 1);
        }
    }

    int num = 0;
    for (int i = 0; i < n; ++i) {
            num = __gcd(num, vec[i]);
    }
    int ops = dp[num];
    int ans = ops + (n-1);
    if (freaky[num] > 0) {
        ans = min(ans, n - freaky[num]);
    }

    printf("%d\n", ans);
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
