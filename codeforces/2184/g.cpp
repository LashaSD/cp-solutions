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

    tree[node] = min(tree[2*node], tree[2*node+1]);
}

int query(int node, int tl, int tr, int l, int r)
{
    if (l > r) {
        return LLONG_MAX;
    }

    if (l <= tl && tr <= r) {
        return tree[node];
    }

    int mid = tl + (tr - tl) / 2;
    int left = query(2*node, tl, mid, l, min(mid, r));
    int right = query(2*node+1, mid+1, tr, max(mid+1, l), r);
    return min(left, right);
}

// 2184G: Nastiness of Segments
void solve()
{
    int n, q;
    cin >> n >> q;
    vector<int> vec(n);
    for (int i = 0; i < n; ++i) {
        cin >> vec[i];
    }

    tree.assign(4*n+4, LLONG_MAX);
    for (int i = 0; i < n; ++i) {
        update(1, 0, n-1, i, vec[i]);
    }

    for (int qi = 0; qi < q; ++qi) {
        int t; cin >> t;
        if (t == 1) {
            int i, x;
            cin >> i >> x;
            update(1, 0, n-1, i-1, x);
        } else {
            int l, r;
            cin >> l >> r;
            l--, r--;
            int bl = l, br = r;
            int save = 0;
            while (bl <= br) {
                int mid = bl + (br - bl) / 2;
                int len = mid - l + 1;
                int mn = query(1, 0, n-1, l, mid);
                if (mn > len -1) {
                    bl = mid +1;
                } else if (mn < len - 1) {
                    br = mid-1;
                } else {
                    save = 1;
                    break;
                }
            }
            cout << save << '\n';
        }
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
