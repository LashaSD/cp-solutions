#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void seg_upd(vector<int>& tree, int node, int tl, int tr, int pos, int val, bool mn = false)
{
    if (tl == tr) {
        tree[node] = val;
        return;
    }

    int mid = tl + (tr - tl) / 2;
    if (pos <= mid) {
        seg_upd(tree, 2*node, tl, mid, pos, val, mn);
    } else {
        seg_upd(tree, 2*node + 1, mid+1, tr, pos, val, mn);
    }

    if (mn) {
        tree[node] = min(tree[2*node], tree[2*node+1]);
    } else {
        tree[node] = max(tree[2*node], tree[2*node+1]);
    }
}

int seg_query(vector<int>& tree, int node, int tl, int tr, int l, int r, bool mn = false)
{
    if (l > r) return mn ? INT_MAX : INT_MIN;

    if (l <= tl && tr <= r) {
        return tree[node];
    }

    int mid = tl + (tr - tl) / 2;
    if (mn) {
        return min(seg_query(tree, 2*node, tl, mid, l, min(mid, r), mn),
                seg_query(tree, 2*node+1, mid+1, tr, max(mid+1, l), r, mn));
    } else {
        return max(seg_query(tree, 2*node, tl, mid, l, min(mid, r)),
                seg_query(tree, 2*node+1, mid+1, tr, max(mid+1, l), r));
    }
}

// 1904D2: Set To Max (Hard Version)
void solve()
{
    int n; cin >> n;
    vector<int> a(n), b(n);
    for (int& x: a)
        cin >> x;

    for (int& x: b)
        cin >> x;

    vector<int> tr_a(4*n + 4);
    vector<int> tr_b(4*n + 4, INT_MAX);
    map<int, vector<int>> oc;

    for (int i = 0; i < n; ++i) {
        seg_upd(tr_a, 1, 0, n-1, i, a[i]);
    }

    for (int i = 0; i < n; ++i) {
        seg_upd(tr_b, 1, 0, n-1, i, b[i], true);
    }

    for (int i = 0; i < n; ++i) {
        int x = a[i];
        oc[x].push_back(i+1);
    }

    for (int i = 0; i < n; ++i) {
        int x = a[i];
        int y = b[i];
        if (x == y) continue;

        vector<int>& pos = oc[y];
        auto r_it = upper_bound(pos.begin(), pos.end(), i+1);
        auto l_it = r_it;
        if (l_it != pos.begin()) l_it--;
        
        bool ok = false;

        if (l_it != pos.end()) {
            int l = *l_it;
            int r = i+1;

            int mx = seg_query(tr_a, 1, 0, n-1, l-1, r-1);
            int mn = seg_query(tr_b, 1, 0, n-1, l-1, r-1, true);

            if (mx == y && mn == y) {
                ok = true;
            }
        }

        if (r_it != pos.end()) {
            int l = i+1;
            int r = *r_it;

            int mx = seg_query(tr_a, 1, 0, n-1, l-1, r-1);
            int mn = seg_query(tr_b, 1, 0, n-1, l-1, r-1, true);

            if (mx == y && mn == y) {
                ok = true;
            }
        }

        if (!ok) {
            cout << "NO\n";
            return;
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
