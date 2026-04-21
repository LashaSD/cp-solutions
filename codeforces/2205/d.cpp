#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2205D: Simons and Beating Peaks
void solve()
{
    int n; cin >> n;
    vector<int> vec(n);
    for (int i = 0; i < n; ++i) {
        cin >> vec[i];
    }

    int logn = 63 - __builtin_clzll(n);
    vector<vector<int>> rmq(logn+1, vector<int>(n+1));
    for (int i = 0; i < n; ++i) {
        rmq[0][i] = i;
    }

    for (int s = 1; s <= logn; ++s) {
        int len = (1ll << s);
        for (int i = 0; i <= n - len; i++) {
            int a = rmq[s-1][i];
            int b = rmq[s-1][i + len/2];
            if (vec[a] > vec[b]) {
                rmq[s][i] = a;
            } else {
                rmq[s][i] = b;
            }
        }
    }

    auto query = [&](int i, int j) {
        int len = j - i + 1;
        int s = 63 - __builtin_clzll(len);
        int a = rmq[s][i];
        int b = rmq[s][j - (1ll << s) + 1];
        if (vec[a] > vec[b]) return a;
        else return b;
    };

    int ans = 0;
    // {index, tl, tr, ans}
    vector<tuple<int, int, int, int>> st;
    st.push_back({query(0, n-1), 0, n-1, 0});
    while (st.size() > 0) {
        int i, tl, tr, x;
        tie(i, tl, tr, x) = st.back();
        st.pop_back();

        int len = tr - tl + 1;
        if (len <= 2) {
            ans = max(ans, x + len);
            continue;
        }

        if (i > tl) {
            int lefti = query(tl, i-1);
            st.push_back({lefti, tl, i-1, x + 1});
        }

        if (i < tr) {
            int righti = query(i+1, tr);
            st.push_back({righti, i+1, tr, x + 1});
        }
    }

    cout << n - ans << '\n';
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
