#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <cstdint>
#include <set>
#include <algorithm>
#include <assert.h>
#include <functional>
#include <map>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2217D: Flip the Bit (Hard Version)
void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> vec(n);
    for (int i = 0; i < n; ++i) {
        cin >> vec[i];
    }

    int x = 0;
    vector<int> bounds;
    bounds.push_back(0);
    for (int i = 0; i < k; ++i) {
        int j; cin >> j;
        j--;
        x = vec[j];
        bounds.push_back(j);
    }
    bounds.push_back(n-1);

    vector<int> blocks;
    for (int i = 0; i < (int)bounds.size()-1; ++i) {
        int l = bounds[i];
        int r = bounds[i+1];
        int cnt = 0;
        for (int j = l; j < r; ++j) {
            if (vec[j] != vec[j+1]) {
                cnt++;
            }
        }
        blocks.push_back(cnt);
    }

    if (vec[0] != x) {
        blocks.front()++;
    }

    if (vec[n-1] != x) {
        blocks.back()++;
    }

    int sum = 0;
    int mx = 0;
    for (int i = 0; i < (int)blocks.size(); ++i) {
        sum += blocks[i];
        mx = max(mx, blocks[i]);
    }

    int ans = max(mx, (sum+1)/2);
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
