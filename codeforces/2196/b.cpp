#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2196B: Another Problem about Beautiful Pairs
void solve()
{
    int n; cin >> n;
    vector<int> vec(n);

    for (int i = 0; i < n; ++i) {
        cin >> vec[i];
    }

    int sqn = sqrt(n) + 1;
    int ans = 0;
    int overcount = 0;
    for (int i = 0; i < n; ++i) {
        int x = vec[i];
        int k = 1;
        for (int rep = 0; rep < 2; ++rep) {
            for (int j = 1; j < sqn; ++j) {
                int index = i + (x*j * k);
                if (index < 0 || index >= n) break;

                if (vec[index] == j) {
                    if (x < sqn) {
                        overcount++;
                    }

                    ans++;
                }
            }

            k = -1;
        }
    }

    cout << ans - (overcount / 2)  << '\n';
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
