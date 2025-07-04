#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

// 2049C: MEX Cycle
void solve()
{
    int n, x, y;
    cin >> n >> x >> y;
    vector<int> vec(n);
    vec[0] = 0;
    for (int i = 1; i < n; ++i) {
        vec[i] = !vec[i-1];
    }

    bool f = false;
    if (vec[n-1] == 0) {
        vec[n-1] = 2;
        f = true;
    }

    if (max(x, y) != n || !f) {
        if (vec[x-1] == vec[y-1]) {
            vec[y-1] = 2;
            if ((y-1) == (n-2) && f) {
                vec[n-1] = 1;
            }

            if ((y-1) == (n-3) && f) {
                vec[n-2] = 0;
                vec[n-1] = 1;
            }
        }
    }

    for (int num : vec)
        cout << num << ' ';
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
