#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

const int maxN = 1e5 + 5;
vector<int> g[maxN + 1];
bool visited[maxN + 1];
int ans[3];
int ears[2] = {-1, -1};
int cnt = 0;

bool is_body(int u, int p) {
    for (int v: g[u]) {
        if (v == p) continue;
        if (g[v].size() == 3) return true;
        if (g[v].size() == 4) return false;
        return is_body(v, u);
    }

    return false;
}

int dfs_tail(int u) {
    visited[u] = 1;
    for (int v: g[u]) {
        if (visited[v]) continue;
        return 1 + dfs_tail(v);
    }

    return 1;
}

int dfs_body_half(int u, int p) {
    if (g[u].size() == 3) {
        if (ears[0] == -1) ears[0] = u;
        else ears[1] = u;

        return 1;
    }

    for (int v: g[u]) {
        if (v == p) continue;
        return 1 + dfs_body_half(v, u);
    }

    return 0;
}

// GYM106035I: Nicka and the goldfish
void solve()
{
    int n; cin >> n;

    for (int i = 0; i < n+2; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    for (int i = 1; i <= n; ++i) {
        if (g[i].size() != 4) continue;
        visited[i] = 1;
        for (int v: g[i]) {
            if (is_body(v, i)) {
                ans[1] += dfs_body_half(v, i) + 1;
            } else if (ans[2] == 0) {
                ans[2] = dfs_tail(v) + 1;
            }
        }
        break;
    }

    ans[1]--;
    ans[0] = n+2 - ans[1] - ans[2] + 1;
    for (int i = 0; i < 3; ++i)
        cout << ans[i] << ' ';
    cout << '\n';
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
