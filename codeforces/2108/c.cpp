#include <iostream>
#include <cassert>
#include <climits>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <map>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2108C: Neo's Escape
void solve()
{
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<pair<int, int>> vec(n);
    for (int i = 0; i < n; ++i) {
        vec[i].xx = a[i];
        vec[i].yy = i;
    }

    sort(vec.begin(), vec.end(), greater<pair<int, int>>());

    int k = 0;
    map<int, set<int>> unvisited;
    map<int, set<int>> q;
    for (auto [x, j]: vec)
        unvisited[x].insert(j);

    for (int i = 0; i < n; ++i) {
        auto [x, _] = vec[i];
        
        int j;
        if (q[x].size() > 0) {
            auto it = q[x].begin();
            j = *it;
            q[x].erase(it);
        } else {
            auto it = unvisited[x].begin();
            j = *it;
            unvisited[x].erase(it);
            k++;
        }

        if (j-1 >= 0) {
            int y = a[j-1];
            set<int>& s = unvisited[y];
            auto it = s.find(j-1);
            if (it != s.end()) {
                s.erase(it);
                q[y].insert(j-1);
            }
        }

        if (j+1 < n) {
            int y = a[j+1];
            set<int>& s = unvisited[y];
            auto it = s.find(j+1);
            if (it != s.end()) {
                s.erase(it);
                q[y].insert(j+1);
            }
        }
    }

    cout << k << '\n';
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
