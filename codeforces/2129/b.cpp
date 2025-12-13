#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

struct FT {
    int n;
    vector<int> tree;
    FT(int _n): n(_n) {
        tree.resize(n+1);
    }
    void updateIndex(int i, int v) {
        for (; i <= n; i += (i & -i)) {
            tree[i] += v;
        }
    }
    int query(int r) const {
        int res = 0;
        for (; r >= 1; r -= (r & -r)) {
            res += tree[r];
        }
        return res;
    }
};

// 2129B: Stay or Mirror
void solve()
{
    int n; cin >> n;
    vector<int> a(n+1), b(n+1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        b[i] = 2*n - a[i];
    }
    
    FT left(2*n+1), right(2*n+1);
    for (int i = 1; i <= n; ++i) {
        left.updateIndex(a[i], 1);
    }

    vector<int> vec(n+1);
    int ans = 0;
    for (int i = n; i >= 1; i--) {
        int av = right.query(a[i]) + (left.query(n) - left.query(a[i]));
        int bv = right.query(b[i]) + (left.query(n) - left.query(b[i]));
        left.updateIndex(a[i], -1);
        if (av < bv) {
            vec[i] = a[i];
            right.updateIndex(a[i], 1);
        } else {
            vec[i] = b[i];
            right.updateIndex(b[i], 1);
        }
    }

    for (int i = 1; i <= n; ++i) {
        ans += right.query(vec[i] - 1);
        right.updateIndex(vec[i], -1);
    }
    cout << ans << '\n';
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
