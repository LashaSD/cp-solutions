#include <bits/stdc++.h>
#include <cassert>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

union Info {
    // zero one two
    int p[3];
    struct {
        int z, o, t;
    };
};

// D. Darius' Wisdom
void solve()
{
    int n; cin >> n;
    vector<int> vec(n);
    for (int i = 0; i < n; ++i) {
        cin >> vec[i];
    }

    vector<Info> tree(4*n+4, {0});
    function<void(int, int, int, int, int)> update = [&](int node, int tl, int tr, int pos, int val) {
        if (tl == tr) {
            tree[node].z = val == 0;
            tree[node].o = val == 1;
            tree[node].t = val == 2;
            return;
        }

        int mid = tl + (tr - tl) / 2;
        int left = 2*node;
        int right = 2*node + 1;
        if (pos > mid)
            update(right, mid+1, tr, pos, val);
        else
            update(left, tl, mid, pos, val);

        tree[node].z = tree[left].z + tree[right].z;
        tree[node].o = tree[left].o + tree[right].o;
        tree[node].t = tree[left].t + tree[right].t;
    };

    function<int(int, int, int, int, int, int)> query = [&](int node, int tl, int tr, int l, int r, int val) {
        if (l > r)
            return -1;

        if (tl == tr)
            return tl;

        int mid = tl + (tr - tl) / 2;
        int left = 2*node;
        int right = 2*node + 1;

        if (tree[right].p[val] > 0)
            return query(right, mid+1, tr, max(mid+1, l), r, val);
        else if (tree[left].p[val] > 0)
            return query(left, tl, mid, l, min(mid, r), val);
        else
            return -1;
    };

    for (int i = 0; i < n; ++i)
        update(1, 0, n-1, i, vec[i]);

    // dbg(query(1, 0, n-1, 0, n-1, 2));

    vector<pair<int, int>> ans;
    for (int i = 0; i < n-1; ++i) {
        int curr = vec[i];
        if (curr != 0) {
            int idx = query(1, 0, n-1, i+1, n-1, curr-1);
            if (idx != -1 && vec[idx] < curr) {
                update(1, 0, n-1, idx, curr);
                swap(vec[idx], vec[i]);
                ans.push_back({i+1, idx+1});
                i--;
            }
        }
    }

    cout << ans.size() << '\n';
    for (pair<int, int> p : ans)
        cout << p.first << ' ' << p.second << '\n';
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
