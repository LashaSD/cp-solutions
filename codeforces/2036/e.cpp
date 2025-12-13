#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2036E: Reverse the Rivers
void solve()
{
    int n, k, q;
    cin >> n >> k >> q;
    vector<vector<int>> vec(k, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) {
            cin >> vec[j][i];
        }
    }

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < k; ++j) {
            vec[j][i] |= vec[j][i - 1];
        }
    }

    for (int qc = 0; qc < q; ++qc) {
        int m; cin >> m;
        int tl = 0, tr = n-1;
        for (int mc = 0; mc < m; ++mc) {
            int r, c;
            char o;
            cin >> r >> o >> c;
            r--;
            vector<int>& col = vec[r];
            if (o == '>') {
                auto it = upper_bound(col.begin(), col.end(), c);
                if (it == col.end()) {
                    tl = n;
                } else {
                    int idx = it - col.begin();
                    tl = max(tl, idx);
                }
            } else if (o == '<') {
                auto it = lower_bound(col.begin(), col.end(), c);
                if (it == col.begin()) {
                    tr = -1;
                } else {
                    it--;
                    int idx = it - col.begin();
                    tr = min(tr, idx);
                }
            }
        }

        if (tl <= tr) {
            cout << tl + 1 << '\n';
        } else {
            cout << -1 << '\n';
        }
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
