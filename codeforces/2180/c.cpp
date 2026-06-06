#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <cstdint>
#include <set>
#include <algorithm>
#include <functional>
#include <map>

#define assert(v) do { if (!(v)) { *(int*)0 = 0; } } while (0)

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2180C: XOR-factorization
void solve()
{
    int n, k;
    cin >> n >> k;

    if (k % 2 == 1) {
        for (int i = 0; i < k; ++i) {
            cout << n << ' ';
        }
        cout << '\n';
        return;
    }

    int bit_cnt = 0;
    for (int i = 32; i >= 0; --i) {
        int bit = (1ll << i);
        if (bit & n) {
            bit_cnt++;
        }
    }

    vector<int> pref(34);
    int final_len = min(k, bit_cnt);
    vector<int> ans(final_len, n);
    int it = 0;
    int len = 0;
    for (int i = 32; i >= 0; --i) {
        int bit = (1ll << i);
        if (n & bit) {
            pref[i] = pref[i+1] + 1;
            ans[it] ^= bit;
            it = (it + 1) % final_len;
            len++;
        } else {
            pref[i] = pref[i+1];
            len = min(len, final_len);
            int sz = (len / 2) * 2;
            for (int j = 0; j < sz; ++j) {
                ans[j] |= bit;
            }
        }
    }

    while ((int)ans.size() < k) {
        ans.push_back(n);
    }

    for (int x: ans) {
        cout << x << ' ';
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


