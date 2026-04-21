#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2061D: Kevin and Numbers
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    ll sum_a = 0, sum_b = 0;
    map<int, int> f;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        sum_a += a[i];
        f[a[i]]++;
    }

    for (int i = 0; i < m; ++i) {
        cin >> b[i];
        sum_b += b[i];
    }

    if (sum_a != sum_b) {
        cout << "NO\n";
        return;
    }

    for (int i = 0; i < m; ++i) {
        int x = b[i];
        vector<int> st;
        st.push_back(x);
        while (st.size() > 0) {
            int t = st.back();
            if (f[t] > 0) {
                f[t]--;
                st.pop_back();
                continue;
            }

            if (t == 1) {
                cout << "NO\n";
                return;
            }

            int l = t / 2, r = (t + 1) / 2;
            st.pop_back();
            st.push_back(l), st.push_back(r);
        }
    }

    cout << "YES\n";
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
