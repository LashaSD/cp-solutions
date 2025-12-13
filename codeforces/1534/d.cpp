#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 1534D: Lost Tree
void solve()
{
    int n; cin >> n;
    vector<vector<bool>> adj(n+1, vector<bool>(n+1));

    cout << "? " << 1 << '\n';
    cout.flush();

    vector<int> odds, evens;
    for (int i = 1; i <= n; ++i) {
        int x; cin >> x;
        if (x == 0) continue;
        if (x == 1) {
            adj[1][i] = 1;
            adj[i][1] = 1;
        }

        if (x % 2 == 0) evens.push_back(i);
        else odds.push_back(i);
    }

    vector<int>& vec = odds;
    if (odds.size() > evens.size())
        vec = evens;

    for (int i = 0; i < (int) vec.size(); ++i) {
        int u = vec[i];
        cout << "? " << u << '\n';
        cout.flush();
        for (int v = 1; v <= n; ++v) {
            int x; cin >> x;
            if (x == 1) {
                adj[u][v] = 1;
                adj[v][u] = 1;
            }
        }
    }

    cout << "!\n";
    for (int i = 1; i <= n; ++i) {
        for (int j = i+1; j <= n; ++j) {
            if (adj[i][j]) {
                cout << i << ' ' << j << '\n';
            }
        }
    }
    cout.flush();
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
