#include <iostream>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <deque>

using namespace std;
using ll = long long;

#define int ll

// 2103D: Local Construction
void solve()
{
    int n; cin >> n;
    vector<int> a(n);
    int m = -1;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        m = max(m, a[i]);
    }

    for (int i = 0; i < n; ++i) {
        if (a[i] == -1) {
            a[i] = m + 1;
            break;
        }
    }

    m++;

    vector<vector<int>> oc(m+1);
    for (int i = 0; i < n; ++i) {
        oc[a[i]].push_back(i);
    }

    vector<int> ans(n, -1);

    bool asc = false;
    int l = 1, r = n;
    for (int i = 1; i <= m; ++i) {
        int br = n-1;
        while (br >= 0 && a[br] <= i) --br;

        for (int j = 0; j < br; ++j) {
            if (a[j] == i) {
                if (asc) {
                    ans[j] = l++;
                } else {
                    ans[j] = r--;
                }
            }
        }

        for (int j = n-1; j > br; --j) {
            if (a[j] == i) {
                if (asc) {
                    ans[j] = l++;
                } else {
                    ans[j] = r--;
                }
            }
        }

        asc = !asc;
    }

    for (int x: ans)
        cout << x << ' ';
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
