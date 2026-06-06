#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <cstdint>
#include <set>
#include <algorithm>
#include <assert.h>
#include <functional>
#include <map>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

vector<int> tree;

void update(int node, int tl, int tr, int pos, int val)
{
    if (tl == tr) {
        tree[node] = val;
        return;
    }

    int mid = tl + (tr - tl) / 2;
    if (pos <= mid) {
        update(2*node, tl, mid, pos, val);
    } else {
        update(2*node+1, mid+1, tr, pos, val);
    }

    tree[node] = tree[2*node] + tree[2*node+1];
}

int query(int node, int tl, int tr, int i)
{
    if (tl == tr) {
        return tr;
    }

    int mid = tl + (tr - tl) / 2;
    if (tree[2*node] >= i) {
        return query(2*node, tl, mid, i);
    } else {
        return query(2*node+1, mid+1, tr, i - tree[2*node]);
    }
}

// ABC449E: A += v
void solve()
{
    int n, m;
    cin >> n >> m;
    tree.resize(4*m+4);
    vector<int> vec(n+1);
    for (int i = 1; i <= n; ++i) {
        cin >> vec[i];
    }

    int q; cin >> q;
    vector<int> qvec(q+1);
    for (int i = 1; i <= q; ++i) {
        cin >> qvec[i];
    }

    vector<int> f(m+1);
    for (int i = 1; i <= n; ++i) {
        f[vec[i]]++;
    }

    vector<pair<int, int>> a;
    for (int x = 1; x <= m; ++x) {
        a.push_back({f[x], x});
    }

    sort(a.begin(), a.end());

    int sz = a.size();
    vector<int> ops(m);
    ops[0] = 1;
    for (int i = 1; i < m; ++i) {
        int diff = a[i].xx - a[i-1].xx;
        ops[i] = ops[i-1] + i * diff;
    }

    vector<int> ans(q+1);

    vector<vector<pair<int, int>>> cat(m+1);
    for (int i = 1; i <= q; ++i) {
        int index = qvec[i];
        if (index <= n) {
            ans[i] = vec[index];
            continue;
        }

        index -= n;
        auto it = --upper_bound(ops.begin(), ops.end(), index);
        int len = it - ops.begin() + 1;
        int k = ((index - *it) % len) + 1;
        cat[len].push_back({i, k});
    }

    for (int p = 1; p <= m; ++p) {
        update(1, 1, m, a[p-1].yy, 1);
        for (auto [i, j]: cat[p]) {
            ans[i] = query(1, 1, m, j);
        }
    }

    for (int i = 1; i <= q; ++i) {
        cout << ans[i] << '\n';
    }
}

int T = 1;
int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(T--)
        solve();

    return 0;
}
