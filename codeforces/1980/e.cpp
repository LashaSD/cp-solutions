#include <algorithm>
#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

const int P = 31;
const int MOD = 1e9 + 9;
const int MAX_N = 2e5 + 5;
ll p_pow[MAX_N];

void precompute() {
    p_pow[0] = 1;
    p_pow[1] = P;
    for (int i = 2 ; i < MAX_N; ++i) {
        p_pow[i] = ((p_pow[i-1] % MOD)  * (P % MOD)) % MOD;
    }
}

// E. Permutation of Rows and Columns
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m)), b(n, vector<int>(m));
    // transposed
    vector<vector<int>> a_t(m, vector<int>(n)), b_t(m, vector<int>(n));

    auto hash = [&](vector<int>& vec) -> ll {
        sort(vec.begin(), vec.end());
        int n = vec.size();
        ll value = 0;

        for (int i = 0; i < vec.size(); ++i) {
            value += ((vec[i] % MOD) * (p_pow[i] % MOD)) % MOD;
        }

        return value;
    };

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
            a_t[j][i] = a[i][j];
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> b[i][j];
            b_t[j][i] = b[i][j];
        }
    }

    vector<ll> row_vals, col_vals;
    unordered_map<ll, ll> row_cnt, col_cnt;
    // a rows
    for (int i = 0; i < n; ++i) {
        ll val = hash(a[i]);
        if (row_cnt[val]++ == 0) {
            row_vals.push_back(val);
        }
    }

    // a cols
    for (int j = 0; j < m; ++j) {
        ll val = hash(a_t[j]);
        dbg(a_t[j]);
        if (col_cnt[val]++ == 0) {
            col_vals.push_back(val);
        }
    }

    unordered_map<ll, ll> b_row, b_col;
    // b rows
    for (int i = 0; i < n; ++i) {
        ll val = hash(b[i]);
        b_row[val]++;
    }

    // b cols
    for (int j = 0; j < m; ++j) {
        ll val = hash(b_t[j]);
        b_col[val]++;
    }

    bool ok = true;
    for (ll val : row_vals) {
        if (row_cnt[val] != b_row[val]) {
            ok = false;
        }
    }

    for (ll val : col_vals) {
        if (col_cnt[val] != b_col[val]) {
            ok = false;
        }
    }

    dbg(col_vals);
    dbg(b_row);
    dbg(b_col);
    dbg(row_cnt);
    dbg(col_cnt);

    cout << (ok ? "YES\n" : "NO\n");
}

int T = 1;
int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    precompute();

    cin >> T;
    while(T--)
        solve();
    return 0;
}
