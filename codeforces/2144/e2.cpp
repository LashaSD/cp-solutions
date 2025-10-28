#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll

const int mod = 998244353;

ll binpow(ll a, ll b) 
{
    ll res = 1;
    a = a % mod;
    while (b > 0){
        if ((b & 1) != 0){
            res = (res * a) % mod;
        }
 
        a = (a * a) % mod;
        b >>= 1LL;
    }
    return res;
}

struct ST {
    int n;
    vector<int> tree;
    vector<int> lazy;

    ST(int _n) 
    {
        n = _n;
        tree.resize(4 * n + 4);
        lazy.resize(4 * n + 4);
    }

    void __setIndex(int node, int tl, int tr, int i, int v) 
    {
        if (tl == tr) {
            tree[node] = v;
            return;
        }

        int mid = tl + (tr - tl) / 2;
        if (i <= mid) {
            __setIndex(2*node, tl, mid, i, v);
        } else {
            __setIndex(2*node + 1, mid+1, tr, i, v);
        }

        // TODO: recomputation
    }

    void __update(int node, int tl, int tr, int l, int r, int m)
    {
        if (l > r) return;

        if (l <= tl && tr <= r) {
            lazy[node] += m;
            return;
        }

        int mid = tl + (tr - tl) / 2;
        __update(2*node, tl, mid, l, min(mid, r), m);
        __update(2*node + 1, mid+1, tr, max(mid+1, l), r, m);
    }

    int __query(int node, int tl, int tr, int i)
    {
        if (tl == tr) {
            if (lazy[node] > 0) {
                tree[node] = (tree[node] * binpow(2, lazy[node])) % mod;
                lazy[node] = 0;
            }

            return tree[node];
        }

        if (lazy[node]) {
            lazy[2*node] += lazy[node];
            lazy[2*node + 1] += lazy[node];
            lazy[node] = 0;
        }

        int mid = tl + (tr - tl) / 2;
        if (i <= mid)
            return __query(2*node, tl, mid, i);
        else
            return __query(2*node+1, mid+1, tr, i);
    }

    void setIndex(int i, int v) 
    {
        __setIndex(1, 0, n-1, i, v);
    }

    void update(int l, int r, int m) 
    {
        __update(1, 0, n-1, l, r, m);
    }
    
    int query(int i)
    {
        return __query(1, 0, n-1, i);
    }
};

// 2144E2: Looking at Towers (difficult version)
void solve()
{
    int n; cin >> n;
    vector<int> vec(n);
    for (int& x: vec)
        cin >> x;

    vector<int> pref(n), suff(n);
    suff.back() = vec.back();
    pref[0] = vec[0];

    vector<int> l_side = { 0 }, r_side = { 0 };
    for (int i = 0; i < n; ++i) {
        if (vec[i] > l_side.back()) {
            l_side.push_back(vec[i]);
        }
    }

    for (int i = n-1; i >= 0; --i) {
        if (vec[i] > r_side.back()) {
            r_side.push_back(vec[i]);
        }
    }

    int mx_num = 0;
    for (int x: vec)
        mx_num = max(mx_num, x);

    int m = l_side.size();
    vector<int> l(n);
    ST dp(m);
    for (int i = 0; i < n; ++i) {
        int x = vec[i];

        auto it = lower_bound(l_side.begin(), l_side.end(), x);
        int idx = it - l_side.begin() - 1;

        if (x == mx_num) {
            if (m >= 3)
                l[i] = (dp.query(m-3) + dp.query(m-2)) % mod;
            else
                l[i] = (dp.query(m-2) + 1) % mod;
        }

        int j = idx;
        if (*it == x && x != vec.front()) {
            int v1 = dp.query(idx);
            int v2 = dp.query(idx - 1);
            dp.setIndex(idx, (2*v1 % mod + v2) % mod);
            //dp[idx] = (2 * dp[idx] % mod + dp[idx - 1]) % mod;
            j++;
        } else if (x == vec.front()) {
            int v = dp.query(idx);
            dp.setIndex(idx, (2 * v % mod + 1) % mod);
            //dp[idx] = (2 * dp[idx] % mod + 1) % mod;
            j++;
        }

        dp.update(j, m-1, 1);
        //for (int k = j; k < m; ++k) {
        //    dp[k] = (2 * dp[k]) % mod;
        //}
    }

    m = r_side.size();
    vector<int> r(n);
    ST pd(m);
    for (int i = n-1; i >= 0; --i) {
        int x = vec[i];

        auto it = lower_bound(r_side.begin(), r_side.end(), x);
        int idx = it - r_side.begin() - 1;

        if (x == mx_num) {
            if (m >= 3)
                r[i] = (pd.query(m-3) + pd.query(m-2)) % mod;
            else
                r[i] = (pd.query(m-2) + 1) % mod;
            continue;
        }

        int j = idx;
        if (*it == x && j > 0) {
            int v1 = pd.query(j);
            int v2 = pd.query(j-1);
            pd.setIndex(j, (2*v1 % mod + v2) % mod);
            //pd[j] = (2 * pd[j] % mod + pd[j - 1]) % mod;
            j++;
        } else if (x == vec.back()) {
            int v1 = pd.query(j);
            //pd[j] = (2 * pd[j] % mod + 1) % mod;
            pd.setIndex(j, (2*v1 % mod + 1) % mod);
            j++;
        }

        pd.update(j, m-1, 1);
        //for (int k = j; k < m; ++k) {
        //    pd[k] = (2 * pd[k]) % mod;
        //}
    }

    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        if (vec[i] != mx_num) continue;
        int x = (l[i] * r[i]) % mod;
        //cerr << "DBG: " << l[i] << ' ' << r[i] << '\n';
        ans = (ans + x) % mod;
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
