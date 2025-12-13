#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 1905D: Cyclic MEX
void solve()
{
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    int N = 2*n;
    vector<int> vec(N);
    for (int i = 0; i < N; ++i) {
        vec[i] = a[i % n];
    }

    set<int> unused;
    for (int i = 0; i <= n; ++i)
        unused.insert(i);

    int sum = 0;
    vector<pair<int, int>> st;
    for (int i = 0; i < n; ++i) {
        int x = vec[i];
        unused.erase(x);
        pair<int, int> m = make_pair(1ll, *unused.begin());
        st.push_back(m);
        sum += m.yy;
    }

    int mx = sum;
    for (int i = 0; i < n; ++i) {
        int x = vec[i];
        // move x to the back
        int f1 = 0;
        while (!st.empty()) {
            auto [f, y] = st.back();
            if (y > x) {
                f1 += f;
                st.pop_back();
                sum -= f*y;
            } else break;
        }

        if (f1 > 0) {
            st.push_back({f1, x});
            sum += f1*x;
        }

        st.push_back({1, n});
        sum += n;
        mx = max(mx, sum);
    }
    cout << mx << '\n';
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
