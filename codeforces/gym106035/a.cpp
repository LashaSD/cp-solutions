#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// GYM106035A: Pyramidal paths
void solve()
{
    int n; cin >> n;
    vector<int> vec(n);
    for (int i = 0; i < n; ++i) {
        cin >> vec[i];
    }

    vector<bool> b(n);
    for (int i = 1; i < n; ++i) {
        b[i] = vec[i] > vec[i-1];
    }

    bool state_change = 0;
    for (int i = 2; i < n; ++i) {
        if (b[i] != b[i-1]) {
            if (state_change) {
                cout << "NO\n";
                return;
            }

            state_change = 1;
        }
    }

    if (!state_change) {
        cout << "NO\n";
        return;
    }

    cout << "YES\n";
}

int T = 1;
int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //cin >> T;
    while(T--)
        solve();

    return 0;
}
