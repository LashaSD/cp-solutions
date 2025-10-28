#include <bits/stdc++.h>

using namespace std;
using ll = long long;
#define int ll

struct Node {
    int l = 0, r = 0;
    int gap = 0;
};

int N = 1e6;
vector<Node> tree(4*N+4);

static inline Node merge(const Node& a, const Node& b)
{
    Node res;

    int l1 = a.l, r1 = a.r, g1 = a.gap;
    int l2 = b.l, r2 = b.r, g2 = b.gap;

    if (l1 == 0) {
        return b;
    } else if (l2 == 0) {
        return a;
    }

    if (l2 >= r1) {
        res.l = l1;
        res.r = r2;
        res.gap = g1 + g2 + l2 - r1;
        //cerr << "DBG: " << res.l << ' ' << res.r << ' ' << res.gap << '\n';
    } else {
        int diff = r1 - l2;
        res.l = l1;
        res.r = r2 + max(0ll, diff - g2);
        res.gap = g1 + max(0ll, g2 - diff);
    }

    return res;
}

void seg_update(int node, int tl, int tr, int t, int d)
{
    if (tl == tr) {
        tree[node].l = d == 0 ? 0 : t+1;
        tree[node].r = tree[node].l + d;
        tree[node].gap = 0;
        return;
    }

    int mid = tl + (tr - tl) / 2;
    if (t <= mid) {
        seg_update(2*node, tl, mid, t, d);
    } else {
        seg_update(2*node + 1, mid+1, tr, t, d);
    }

    tree[node] = merge(tree[2*node], tree[2*node+1]);
}

Node seg_query(int node, int tl, int tr, int l, int r)
{
    if (l > r) {
        return Node{};
    }

    if (l <= tl && tr <= r) {
        return tree[node];
    }

    int mid = tl + (tr - tl) / 2;
    Node a = seg_query(2*node, tl, mid, l, min(mid, r));
    Node b = seg_query(2*node + 1, mid+1, tr, max(l, mid+1), r);

    return merge(a, b);
}

static inline void update(int t, int d)
{
    seg_update(1, 0, N-1, t-1, d);
}

static inline Node query(int t)
{
    return seg_query(1, 0, N-1, 0, t-1);
}

// 1089K: King Kog's Reception
void solve()
{
    int q; cin >> q;
    vector<pair<int, int>> qvec(q);
    for (int qq = 0; qq < q; ++qq) {
        char c; cin >> c;
        if (c == '+') {
            int t, d;
            cin >> t >> d;
            qvec[qq].first = t;
            qvec[qq].second = d;
            update(t, d);
        } else if (c == '-') {
            int i; cin >> i;
            update(qvec[i-1].first, 0);
        } else if (c == '?') {
            int t; cin >> t;
            Node a = query(t);
            cout << max(0ll, a.r - t) << '\n';
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
