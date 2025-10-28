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

const int INF = 4e9;

struct ST {
    int n;
    vector<int> tree;

    ST(int _n): n(_n) {
        tree.resize(4 * n + 4);
    }

    void _update(int node, int tl, int tr, int i, int y)
    {
        if (tl == tr) {
            tree[node] = y;
            return;
        }

        int mid = tl + (tr - tl) / 2;
        if (i <= mid) {
            _update(2 * node, tl, mid, i, y);
        } else {
            _update(2 * node + 1, mid + 1, tr, i, y);
        }
        
        tree[node] = max(tree[2*node], tree[2*node+1]);
    }

    int _query_l(int node, int tl, int tr, int i, int y)
    {
        if (tl > i) return -INF;
        if (2*tree[node] <= y) return -INF;

        if (tl == tr) return tl;

        int mid = tl + (tr - tl) / 2;

        if (tr <= i) {
            if (2*tree[2*node + 1] > y) {
                return _query_l(2 * node + 1, mid+1, tr, i, y);
            } else if (2*tree[2*node] > y) {
                return _query_l(2*node, tl, mid, i, y);
            }
        }

        int a = _query_l(2*node + 1, mid+1, tr, i, y);
        if (a != -INF) return a;

        return _query_l(2*node, tl, mid, i, y);
    }

    int _query_r(int node, int tl, int tr, int i, int y)
    {
        if (tr < i) return -INF;
        if (2*tree[node] <= y) return -INF;

        if (tl == tr) return tl;

        int mid = tl + (tr - tl) / 2;

        if (tl >= i) {
            if (2*tree[2*node] > y) {
                return _query_r(2*node, tl, mid, i, y);
            } else if (2*tree[2*node + 1] > y) {
                return _query_r(2 * node + 1, mid+1, tr, i, y);
            }
        }

        int a = _query_r(2*node, tl, mid, i, y);
        if (a != -INF) return a;

        return _query_r(2*node + 1, mid+1, tr, i, y);
    }

    inline void update(int i, int y) 
    {
        _update(1, 0, n-1, i, y);
    }

    inline int query_l(int i, int y)
    {
        return _query_l(1, 0, n-1, i, y);
    }

    inline int query_r(int i, int y)
    {
        return _query_r(1, 0, n-1, i, y);
    }
};

// gym101630A: Archery Tournament
void solve()
{
    int n;
    cin >> n;
    vector<pair<int, pair<int, int>>> qvec(n);

    set<int> xs;

    for (int i = 0; i < n; ++i) {
        int t; cin >> t;
        int x, y;
        cin >> x >> y;

        xs.insert(x);
        qvec[i].first = t;
        qvec[i].second.first = x;
        qvec[i].second.second = y;
    }

    map<int, int> x_comp;
    map<int, int> comp_x;
    int id = 0;
    for (auto x: xs) {
        x_comp[x] = id;
        comp_x[id] = x;
        id++;
    }

    vector<int> x_id(id);
    ST tree(id);

    for (int i = 0; i < n; ++i) {
        auto q = qvec[i];
        int t = q.first;
        auto [x, y] = q.second;
        if (t == 1) {
            tree.update(x_comp[x], y);
            x_id[x_comp[x]] = i;
        } else if (t == 2) {
            int ret_l = tree.query_l(x_comp[x], y);
            int ret_r = tree.query_r(x_comp[x], y);

            // cerr << "QUERY: " << i << '\n';
            if (ret_l >= 0) {
                int j = x_id[ret_l];
                auto [x1, y1] = qvec[j].second;
                // cerr << "    L: (" << x1 << ", " << y1 << ")\n";
                if ((x - x1)*(x - x1) + (y - y1)*(y - y1) < y1*y1) {
                    cout << j + 1 << '\n';
                    tree.update(ret_l, 0);
                    continue;
                }
            }

            if (ret_r >= 0) {
                int j = x_id[ret_r];
                auto [x1, y1] = qvec[j].second;
                // cerr << "    R: (" << x1 << ", " << y1 << ")\n";
                if ((x - x1)*(x - x1) + (y - y1)*(y - y1) < y1*y1) {
                    cout << j + 1 << '\n';
                    tree.update(ret_r, 0);
                    continue;
                }
            }

            cout << -1 << '\n';
        }
    }
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
