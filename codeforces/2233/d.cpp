#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <cstdint>
#include <set>
#include <cstdio>
#include <algorithm>
#include <functional>
#include <map>

#define assert(v) do { if (!(v)) { *(int*)0 = 0; } } while (0)

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2233D: Goods on the Shelf
bool check(vector<int> &vec, int l = 0, int r = 0)
{
    int n = vec.size();
    l = min(n-1, max(l, 0ll));
    r = min(n-1, max(r, 0ll));
    swap(vec[l], vec[r]);
    vector<bool> vis(n+1);

    for (int i = 1; i < n; ++i) {
        if (vis[vec[i]]) {
            swap(vec[l], vec[r]);
            return false;
        }

        if (vec[i] != vec[i-1]) {
            vis[vec[i-1]] = 1;
        }
    }

    swap(vec[l], vec[r]);
    return true;
}

void solve()
{
    int n; cin >> n;
    vector<int> vec(n);
    int num = 1;
    map<int, int> id;
    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        if (id.count(x) == 0) {
            id[x] = num++;
        }

        vec[i] = id[x];
    }

    if (check(vec)) {
        cout << "YES\n";
        return;
    }

    // segs[x] = segments for value x
    vector<vector<pair<int, int>>> segs(num+1);
    for (int i = 0; i < n; ++i) {
        if (i == 0 || vec[i] != vec[i-1]) {
            segs[vec[i]].push_back({i, i});
        } else {
            segs[vec[i]].back().yy = i;
        }
    }

    for (int x = 1; x <= num; ++x) {
        vector<pair<int, int>> &s = segs[x];
        if (s.size() > 3) {
            cout << "NO\n";
            return;
        }

        if (s.size() >= 2) {
            for (int i1 = 0; i1 < (int)s.size(); ++i1) {
                for (int i2 = i1+1; i2 < (int)s.size(); ++i2) {
                    auto [l1, r1] = s[i1];
                    auto [l2, r2] = s[i2];
                    bool ok = 0;

                    ok |= check(vec, l1-1, l2);
                    ok |= check(vec, l1-1, r2);
                    ok |= check(vec, l1, l2-1);
                    ok |= check(vec, l1, r2+1);

                    ok |= check(vec, r1+1, l2);
                    ok |= check(vec, r1+1, r2);
                    ok |= check(vec, r1, l2-1);
                    ok |= check(vec, r1, r2+1);

                    if (ok) {
                        cout << "YES\n";
                        return;
                    }
                }
            }

            cout << "NO\n";
            return;
        }
    }
}

int T = 1;
int32_t main(void)
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    cin >> T;
    while(T--)
        solve();

    return 0;
}
