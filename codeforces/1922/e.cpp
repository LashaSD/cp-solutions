#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 1922E: Increasing Subsequences
void solve()
{
    ll x;
    cin >> x;
    x--;
    vector<int> nums;
    int ops = 0;
    bool have_bits = 0;
    while (x > 0) {
        ll curr = 0;
        for (int i = 0; i < 64; ++i) {
            ll p = (1ll << i);
            if (!have_bits && curr + p > x) {
                x -= curr;
                nums.push_back(i);
                have_bits = 1;
                break;
            } else if (have_bits && p > x) {
                nums.push_back(i-1);
                x -= (1ll << (i-1));
                break;
            }

            curr += p;
        }
    }

    vector<int> ans;
    ll counter = 1e9;
    {
        int bits = nums[0];
        counter -= bits;
        for (int i = 1; i <= bits; ++i) {
            ans.push_back(counter + i);
        }
    }

    for (size_t i = 1; i < nums.size(); ++i) {
        int pow = nums[i];
        ans.push_back(counter + 1 + pow);
    }

    cout << ans.size() << '\n';
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
