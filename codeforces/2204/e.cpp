#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <cstdint>
#include <set>
#include <algorithm>
#include <assert.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2204E: Sum of Digits (and Again)
void solve()
{
    string s; cin >> s;
    vector<int> f(10), g(10);
    int n = s.size();
    for (int i = 0; i < n; ++i) {
        f[s[i] - '0']++;
    }

    if (n == 1) {
        cout << s << '\n';
        return;
    }

    for (int x = 1; x <= n*9; ++x) {
        for (int d = 0; d <= 9; ++d) {
            g[d] = f[d];
        }

        {
            int num = x;
            bool should_cont = false;
            while (num > 0) {
                int d = num % 10;
                if (g[d] > 0) {
                    g[d]--;
                } else {
                    should_cont = 1;
                    break;
                }

                num /= 10;
            }

            if (should_cont) continue;
        }

        vector<int> nums;
        nums.push_back(x);
        bool should_cont = 0;
        while (nums.back() > 9) {
            int num = nums.back();
            int dgt_sum = 0;
            while (num > 0) {
                int d = num % 10;
                dgt_sum += d;
                num /= 10;
            }

            num = dgt_sum;
            while (num > 0) {
                int d = num % 10;
                if (g[d] > 0) {
                    g[d]--;
                } else {
                    should_cont = 1;
                    break;
                }

                num /= 10;
            }

            if (should_cont) break;
            nums.push_back(dgt_sum);
        }

        if (should_cont) continue;

        ll sum = 0;
        for (int d = 0; d <= 9; ++d) {
            sum += d * g[d];
        }

        if (sum == x) {
            for (int d = 9; d >= 0; --d) {
                for (int i = 0; i < g[d]; ++i) {
                    cout << d;
                }
            }

            for (int num: nums) {
                cout << num;
            }
            cout << '\n';
            return;
        }
    }

    assert(false);
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
