#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;
using pipii = array<int, 3>;

const int MAX_N = 1e5 + 5;
vector<pair<int, int>> adj[MAX_N];

// 1255C: League of Leesins
void solve()
{
    int n; cin >> n;
    vector<pipii> vec(n-2);
    for (auto& q: vec)
        cin >> q[0] >> q[1] >> q[2];

    for (int i = 0; i < vec.size(); ++i) {
        auto& q = vec[i];
        for (int j = 0; j < 3; ++j) {
            adj[q[j]].push_back({i, j});
        }
    }

    int start = -1;
    for (int i = 1; i <= n; ++i) {
        dbg(i, adj[i]);
        if (adj[i].size() == 1) {
            start = i;
            break;
        }
    }

    vector<int> ans;
    ans.reserve(n);
    // setup start
    int i = adj[start].front().first;
    int j = adj[start].front().second;
    int mid = -1, edge = -1;
    for (int k = 0; k < 3; ++k) {
        if (k == j) continue;
        int num = vec[i][k];
        if (adj[num].size() == 2)
            mid = num;
        else
            edge = num;
    }
    ans.push_back(start);
    ans.push_back(mid);
    ans.push_back(edge);

    int cnt = 3;
    while (true) {
        // find another triple where both mid and edge are present
        dbg(adj[mid]);
        int next_i = -1;
        for (auto k: adj[mid]) {
            int loc_i = k.first, loc_j = k.second;
            if (loc_i == i) continue;
            auto found_it = find(begin(vec[loc_i]), end(vec[loc_i]), edge);
            if (found_it != end(vec[loc_i])) {
                next_i = loc_i;
                break;
            }
        }

        if (next_i == -1) break;

        // find the third number in the new triple
        int new_num = -1;
        for (int k: vec[next_i]) {
            if (k == edge || k == mid) continue;
            new_num = k;
        }

        mid = edge;
        edge = new_num;
        i = next_i;
        ans.push_back(new_num);
    }

    for (int num: ans)
        cout << num << ' ';
    cout << '\n';
}

int T = 1;
int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // cin >> T;
    while(T--)
        solve();
    return 0;
}
