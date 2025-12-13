#include <bits/stdc++.h>

using namespace std;

template<typename T, class Upd>
struct ST {
    size_t n;
    vector<T> tree;
    vector<int> lazy;
    Upd merge;
    T zero;

    ST(int _n, T _zero): n(_n), zero(_zero) {
        tree.resize(4*n + 4, zero);
        lazy.resize(4*n + 4, 0);
    }

    void _push(int node, int tl, int tr)
    {
        if (lazy[node] > 0) {
            tree[node] = lazy[node]*(tr - tl + 1);
            if (tl != tr) {
                lazy[2*node] = lazy[node];
                lazy[2*node + 1] = lazy[node];
            }

            lazy[node] = 0;
        }
    }

    void _setIndex(int node, int tl, int tr, int i, T v)
    {
        _push(node, tl, tr);

        if (tl == tr) {
            tree[node] = v;
            return;
        }

        int mid = tl + (tr - tl) / 2;
        if (i <= mid) {
            _setIndex(2*node, tl, mid, i, v);
        } else {
            _setIndex(2*node+1, mid+1, tr, i, v);
        }

        tree[node] = merge(tree[2*node], tree[2*node+1]);
    }

    void setIndex(int i, T v)
    {
        return _setIndex(1, 0, n-1, i, v);
    }

    void _update(int node, int tl, int tr, int l, int r, T v)
    {
        _push(node, tl, tr);

        if (l > r) return;

        if (l <= tl && tr <= r) {
            lazy[node] = lazy[node] + v;
            _push(node, tl, tr);
            return;
        }

        int mid = tl + (tr - tl) / 2;
        _update(2*node, tl, mid, l, min(mid, r));
        _update(2*node+1, mid+1, tr, max(mid+1, l), r);
        tree[node] = merge(tree[2*node], tree[2*node+1]);
    }

    void update(int l, int r, T v)
    {
        _update(1, 0, n-1, l, r, v);
    }

    T _query(int node, int tl, int tr, int l, int r)
    {
        _push(node, tl, tr);

        if (l > r) {
            return zero;
        }

        if (l <= tl && tr <= r) {
            return tree[node];
        }

        int mid = tl + (tr - tl) / 2;
        T a = _query(2*node, tl, mid, l, min(r, mid));
        T b = _query(2*node+1, mid+1, tr, max(mid+1, l), r);

        return merge(a, b);
    }

    T query(int l, int r)
    {
        return _query(1, 0, n-1, l, r);
    }
};

struct SegUpd {
    long long operator()(long long a, long long b) const { return a + b; }
};

int main()
{
    using ll = long long;
    ll n, q;
    cin >> n >> q;
    ST<ll, SegUpd> tree(n, 0);

    for (int i = 0; i < n; ++i) {
        ll x; cin >> x;
        tree.setIndex(i, x);
    }

    for (int qq = 0; qq < q; ++qq) {
        int t; cin >> t;

        if (t == 1) {
            int l, r;
            ll u;
            cin >> l >> r >> u;
            tree.update(l-1, r-1, u);
        } else {
            int k; cin >> k;
            cout << tree.query(k-1, k-1) << '\n';
        }
    }
}
