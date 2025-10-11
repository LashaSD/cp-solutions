#include <iostream>
#include <vector>
#include <cstdint>
#include <string>
#include <algorithm>
#include <set>

using namespace std;
using ll = long long;

#define int ll

const int mod = 1e9 + 7;
const int maxBit = 63;
vector<int> dp(maxBit + 1, 0);

void precompute()
{
    dp[1] = 1;
    for (int i = 2; i <= maxBit; ++i) {
        dp[i] = i;
        for (int j = 1; j < i; ++j) {
            dp[i] = (dp[i] * dp[j]) % mod;
        }
    }
}

// 2131G: Wafu!
void solve()
{
    int n, k;
    cin >> n >> k;

    vector<int> vec(n);
    for (int& x: vec)
        cin >> x;

    sort(vec.begin(), vec.end(), greater<int>());

    ll ans = 1;
    while (k > 0) {
        int x = vec.back();
        
        if (x <= 31) {
            int num = (1ll << (x - 1));
            if (num <= k) {
                k -= (1ll << (x - 1));
                ans = (ans * dp[x]) % mod;
                vec.pop_back();
                continue;
            }
        }

        k--;
        ans = (ans * x) % mod;
        for (int i = 1; k > 0; ++i) {
            int num = (1ll << (i - 1));
            if (num > k) {
                k--;
                ans = (ans * i) % mod;
                i = 0;
                continue;
            }

            k -= num;
            ans = (ans * dp[i]) % mod;
        }

        break;
    }

    cout << ans << '\n';
}

int T = 1;
int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    precompute();

    cin >> T;
    while(T--)
        solve();
    return 0;
}
