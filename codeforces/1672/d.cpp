#include <bits/stdc++.h>
#include <cassert>
#include <filesystem>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

// 1672D: Cyclic Rotation
void solve()
{
    int n; cin >> n;
    unordered_map<int, set<int>> blocks;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];

    for (int i = 0; i < n; ++i)
        cin >> b[i];

    for (int i = 0; i < n-1; ++i) {
        if (b[i] == b[i+1]) {
            blocks[b[i]].insert(i);
        }
    }

    int u = 0, d = 0;
    set<int> blacklist;
    while (u < n && d < n) {
        while (a[u] == b[d] && u < n && d < n) {
            u++, d++;
            while (blacklist.find(d) != blacklist.end()) {
                d++;
            }
        }

        while (a[u] != b[d] && u < n && d < n) {
            set<int>& num_set = blocks[a[u]];
            auto block_it = num_set.lower_bound(d);
            if (block_it == num_set.end()) {
                dbg(u, d);
                cout << "NO\n";
                return;
            }
            blacklist.insert(*block_it);
            num_set.erase(block_it);
            u++;
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
