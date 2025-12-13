#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 1974G: Money Buys Less Happiness Now 
void solve()
{
    int m, x;
    cin >> m >> x;
    vector<int> c(m+1);
    for (int i = 1; i <= m; ++i) {
        cin >> c[i];
    }

    multiset<int> st;
    int ans = 0;
    int spent = 0;
    for (int i = 1; i <= m; ++i) {
        int coins = (i-1)*x - spent;
        if (coins >= c[i]) {
            spent += c[i];
            st.insert(c[i]);
            ans++;
        } else if (st.size() > 0) {
            auto it = --st.end();
            if (*it > c[i]) {
                spent -= *it - c[i];
                st.erase(it);
                st.insert(c[i]);
            }
        }
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
