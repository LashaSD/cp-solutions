#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2185F: BattleCows
void solve()
{
    int bitn, q;
    cin >> bitn >> q;
    int n = (1ll << bitn);
    // tree[node] == -1 -> not initialized
    vector<int> tree(4*n + 4, -1);

    function<void(int, int, int, int, int)> add = [&](int node, int tl, int tr, int i, int c) {
        if (tl == tr) {
            tree[node] = c;
            return;
        }

        int mid = tl + (tr - tl) / 2;
        int left = 2 * node;
        int right = 2 * node + 1;
        if (i <= mid) {
            add(left, tl, mid, i, c);
        } else {
            add(right, mid+1, tr, i, c);
        }

        if (tree[right] != -1 && tree[left] != -1) {
            tree[node] = tree[right] ^ tree[left];
        }
    };

    function<pair<int,int>(int, int, int, int, int)> query = [&](int node, int tl, int tr, int i, int c) -> pair<int, int> {
        if (tl == tr) {
            return {0, c};
        }

        int mid = tl + (tr - tl) / 2;
        int left = 2 * node;
        int right = 2 * node + 1;
        if (i <= mid) {
            auto [cnt, res] = query(left, tl, mid, i, c);

            if (tree[right] > res) {
                // cerr << "RIGHT: " << tl << ' ' << tr << '\n';
                // right wins
                cnt += mid - tl + 1;
            }

            return {cnt, res ^ tree[right]};
        } else {
            auto [cnt, res] = query(right, mid+1, tr, i, c);

            if (tree[left] >= res) {
                // left wins
                // cerr << "LEFT: " << tl << ' ' << tr << '\n';
                cnt += tr - mid;
            }

            return {cnt, res ^ tree[left]};
        }
    };

    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        add(1, 1, n, i+1, x);
    }

    for (int qi = 0; qi < q; ++qi) {
        int i, c;
        cin >> i >> c;
        auto [ans, _] = query(1, 1, n, i, c);
        cout << ans << '\n';
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
