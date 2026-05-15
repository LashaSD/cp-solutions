#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 1889B: Doremy's Connecting Plan
void solve()
{
    int n, c;
    cin >> n >> c;
    vector<int> vec(n+1), diffs(n+1);
    for (int i = 1; i <= n; ++i) {
        cin >> vec[i];
        diffs[i] = vec[i] - i*c;
    }

    vector<int> v(n+1);
    for (int i = 1; i <= n; ++i)
        v[i] = i;

    sort(v.begin() + 2, v.end(), [&](int a, int b) {
        return diffs[a] > diffs[b];
    });

    int comp_sum = vec[1];
    for (int i = 2; i <= n; ++i) {
        int j = v[i];
        if (diffs[j] + comp_sum >= 0) {
            comp_sum += vec[j];
        } else {
            cout << "NO\n";
            return;
        }
    }

    cout << "YES\n";
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
