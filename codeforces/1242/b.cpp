#include <climits>
#include <functional>
#include <set>
#include <cstdio>
#include <algorithm>
#include <cstdint>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

// B. 0-1 MST
void solve()
{
    int n, m;
    scanf("%d %d", &n, &m);
    vector<unordered_set<int>> g(n+1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].insert(v);
        g[v].insert(u);
    }

    set<int> unvisited;
    for (int u = 1; u <= n; ++u)
        unvisited.insert(u);

    int k = 0;
    for (int i = 1; i <= n; ++i) {
        if (unvisited.find(i) == unvisited.end()) continue;

        queue<int> q;
        q.push(i);
        unvisited.erase(i);
        k++;

        while (not q.empty()) {
            int u = q.front();
            q.pop();

            vector<int> to_erase;
            for (int v : unvisited) {
                if (g[u].count(v) == 0) {
                    to_erase.push_back(v);
                }
            }

            for (int v : to_erase) {
                unvisited.erase(v);
                q.push(v);
            }
        }
    }

    printf("%d", k-1);
}

int T = 1;
int32_t main(void)
{
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    // scanf("%d", &T);
    while(T--)
        solve();
    return 0;
}
