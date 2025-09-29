#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll

// ABC379F: Building 2
void solve()
{
    int n, q;
    cin >> n >> q;
    vector<int> vec(n);
    for (int& x: vec)
        cin >> x;

    int block_size = 63 - __builtin_clzll(n);
    vector<vector<int>> rmq(n, vector<int>(block_size + 1));

    for (int i = 0; i < n; ++i)
        rmq[i][0] = vec[i];

    for (int s = 1; s <= block_size; s++) {
        for (int i = 0; i < n-(1ll << (s-1)); ++i) {
            rmq[i][s] = max(rmq[i][s-1], rmq[i+(1ll << (s-1))][s-1]);
        }
    }

    auto get = [&rmq](int l, int r) {
        int len = r - l + 1;
        int pow = 63 - __builtin_clzll(len);
        return max(rmq[l][pow], rmq[r - (1ll << pow) + 1][pow]);
    };

    vector<int> b(n+1); 
    stack<int> st;
    for (int i = n-1; i >= 0; --i) {
        while (!st.empty()) {
            if (st.top() >= vec[i]) break;
            st.pop();
        }

        st.push(vec[i]);
        b[i] = st.size();
    }

    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;

        int mx = get(l, r-1);
        int tl = r, tr = n-1;

        if (r == n || get(r, n-1) < mx) {
            cout << 0 << '\n';
            continue;
        }

        while (tl != tr) {
            int mid = tl + (tr - tl) / 2;

            int left = get(tl, mid);
            int right = get(mid+1, tr);


            if (left >= mx) {
                tr = mid;
            } else {
                tl = mid+1;
            }
        }

        cout << b[tl] << '\n';
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
