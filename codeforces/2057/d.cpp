#include <vector>
#include <iostream>
#include <cstdint>
#include <set>
#include <algorithm>

using namespace std;
using ll = long long;

#define int ll

const int INF = LLONG_MAX;

struct Node {
    int mn_l = INF; 
    int mn_r = INF;
    int mx_l = -INF;
    int mx_r = -INF;
    int ans_l = 0;
    int ans_r = 0;
};

vector<int> vec;
vector<Node> tree;

static inline Node merge(Node a, Node b)
{
    Node res;

    res.ans_l = max({a.ans_l, b.ans_l, b.mx_l - a.mn_l});
    res.ans_r = max({a.ans_r, b.ans_r, a.mx_r - b.mn_r});
    
    res.mn_l = min(a.mn_l, b.mn_l);
    res.mn_r = min(a.mn_r, b.mn_r);

    res.mx_l = max(a.mx_l, b.mx_l);
    res.mx_r = max(a.mx_r, b.mx_r);

    return res;
}

void seg_update(int node, int tl, int tr, int p, int x1, int x2)
{
    if (tl == tr) {
        tree[node].mn_l = x1;
        tree[node].mn_r = x2;

        tree[node].mx_l = x1;
        tree[node].mx_r = x2;

        tree[node].ans_l = 0;
        tree[node].ans_r = 0;
        return;
    }

    int mid = tl + (tr - tl) / 2;
    if (p <= mid) {
        seg_update(2*node, tl, mid, p, x1, x2);
    } else {
        seg_update(2*node + 1, mid + 1, tr, p, x1, x2);
    }

    tree[node] = merge(tree[2*node], tree[2*node + 1]);
}

// 2057D: Gifts Order
void solve()
{
    int n, q;
    cin >> n >> q;

    tree.clear();
    tree.resize(4 * n + 4);
    
    vec.clear();
    vec.resize(n);

    for (int i = 0; i < n; ++i)
        cin >> vec[i];

    for (int i = 0; i < n; ++i) {
        seg_update(1, 0, n-1, i, vec[i] - i, vec[i] - (n - 1 - i));
    }

    cout << max(tree[1].ans_l, tree[1].ans_r) << '\n';
    for (int i = 0; i < q; ++i) {
        int p, x;
        cin >> p >> x;
        p--;

        vec[p] = x;
        seg_update(1, 0, n-1, p, x - p, x - (n - 1 - p));

        cout << max(tree[1].ans_l, tree[1].ans_r) << '\n';
    }
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
