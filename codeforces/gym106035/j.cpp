#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

int n, k, c;
vector<pair<int, int>> vec;

bool ok(int i) 
{
    int l = i, r = i + k-1;
    if (r > n) return false;

    for (auto [t, c]: vec) {
        if (r/t - (l-1)/t != c) {
            return false;
        }
    }

    return true;
}

// GYM106035J: Battleship
void solve()
{
    cin >> n >> k >> c;
    vec.resize(c);
    for (int i = 0; i < c; ++i) {
        cin >> vec[i].xx >> vec[i].yy;
    }

    for (int i = 1; i <= n; ++i) {
        if (ok(i)) {
            cout << i << '\n';
            return;
        }
    }

    cout << -1 << '\n';
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
