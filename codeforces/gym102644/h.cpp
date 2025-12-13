#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using i32 = int32_t;
using u32 = uint32_t;

const int mod = 1e9 + 7;

#define int ll
#define xx first
#define yy second

using M2x2 = array<int, 4>;
using M1x2 = array<int, 2>;

static inline M2x2 mult2x2(const M2x2& a, const M2x2& b)
{
    M2x2 res = {0, 0, 0, 0};
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                res[2*i + j] = res[2*i + j] + (a[2*i + k]*b[2*k + j] % mod) % mod;
            }
        }
    }

    return res;
}

static inline M1x2 mult1x2(const M1x2& a, const M2x2& b) 
{
    M1x2 res = {0, 0};
    for (int i = 0; i < 1; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                res[1*i + j] = res[1*i + j] + (a[1*i + k]*b[2*k + j] % mod) % mod;
            }
        }
    }

    return res;
}

const M2x2 id = {1, 0, 0, 1};

struct ST {
    int n;
    vector<M2x2> tree;
    ST(int n): n(n) {
        tree.resize(4*n + 4, id);
    }

    M2x2 _query(int node, int tl, int tr, int l, int r)
    {
        if (l > r) return id;

        if (l <= tl && tr <= r) {
            return tree[node];
        }

        int mid = tl + (tr - tl) / 2;
        M2x2 lhs = _query(2*node, tl, mid, l, min(mid, r));
        M2x2 rhs = _query(2*node+1, mid+1, tr, max(mid+1, l), r);

        return mult2x2(lhs, rhs);
    }

    void _setIndex(int node, int tl, int tr, int pos, const M2x2& v)
    {
        if (tl == tr) {
            tree[node] = v;
            return;
        }

        int mid = tl + (tr - tl) / 2;
        if (pos <= mid) {
            _setIndex(2*node, tl, mid, pos, v);
        } else {
            _setIndex(2*node+1, mid+1, tr, pos, v);
        }

        tree[node] = mult2x2(tree[2*node], tree[2*node+1]);
    }

    inline M2x2 query(int l, int r)
    {
        return _query(1, 0, n-1, l, r);
    }

    inline void setIndex(int pos, const M2x2& v)
    {
        _setIndex(1, 0, n-1, pos, v);
    }
};

const M2x2 vowel_mat = {0, 1, 1, 0};
const M2x2 sad_mat = {1, 0, 1, 0};
const M2x2 happy_mat = {0, 1, 0, 1};
const M2x2 all_mat = {20, 6, 7, 19};

static inline M2x2 map_to_matr(char c)
{
    if (c == '?')
        return all_mat;
    else if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
        return vowel_mat;
    else if (c == 'H')
        return happy_mat;
    else if (c == 'S' || c == 'D')
        return sad_mat;

    return id;
}

// Matrix Exponentiation:
// GYM102644H: String Mood Updates
void solve()
{
    int n, q;
    cin >> n >> q;
    string s; cin >> s;

    M1x2 dp1 = {0, 1};
    M1x2 dp2 = {0, 1};

    ST tree(n);
    for (int i = 0; i < n; ++i) {
        tree.setIndex(i, map_to_matr(s[i]));
    }

    dp2 = mult1x2(dp1, tree.tree[1]);

    cout << dp2[1] << '\n';
    for (int qi = 0; qi < q; ++qi) {
        int i;
        char c;
        cin >> i >> c;
        tree.setIndex(i - 1, map_to_matr(c));
        dp2 = mult1x2(dp1, tree.tree[1]);
        cout << dp2[1] << '\n';
    }
}

int T = 1;
int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //cin >> T;
    while(T--)
        solve();

    return 0;
}
