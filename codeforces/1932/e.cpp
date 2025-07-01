#include <algorithm>
#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

// E. Final Countdown
void solve()
{
    int n; cin >> n;
    string s; cin >> s;
    int sum = 0;
    vector<int> ans(n * 4, 0);
    for (int i = 0; i < n; ++i) {
        sum += s[i] - '0';
    }

    for (int i = n-1, j = 0; i >= 0; --i, ++j) {
        // add sum
        int num = sum;
        int k = j;
        while (num > 0) {
            ans[k] += num % 10;
            int l = k;
            while (ans[l] > 9) {
                ans[l+1] += ans[l] / 10;
                ans[l] %= 10;
                l++;
            }
            k++;
            num /= 10;
        }

        sum -= s[i] - '0';
    }

    reverse(ans.begin(), ans.end());
    bool f = false;
    for (int i = 0; i < ans.size(); ++i) {
        if (ans[i] != 0)
            f = true;
        if (f)
            cout << ans[i];
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
