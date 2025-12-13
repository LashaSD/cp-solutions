#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

vector<int> f;
vector<int> f_pref;
void precompute()
{
    ll mx = 1e11;
    ll a = 1, b = 1, c = 2;
    f.push_back(a);
    f.push_back(b);
    for (; b < mx;) {
        a = b;
        b = c;
        c = a + b;
        f.push_back(b);
    }

    f_pref.push_back(1);
    while (f_pref.back() <= mx) {
        f_pref.push_back(f_pref.back() + f[f_pref.size()]);
    }
}

// 1718B: Fibonacci Strings
void solve()
{
    int n; cin >> n;
    vector<int> a(n);
    ll sum = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        sum += a[i];
    }

    auto sz_it = lower_bound(f_pref.begin(), f_pref.end(), sum);
    if (*sz_it != sum) {
        cout << "NO\n";
        return;
    }

    int m = sz_it - f_pref.begin();

    int locked = -1;
    multiset<int> st;
    for (int i = 0; i < n; ++i) {
        st.insert(a[i]);
    }

    while (m >= 0) {
        if (st.size() == 0) {
            cout << "NO\n";
            return;
        }

        int need = f[m];
        auto it = --st.end();
        int x = *it;
        if (x < need) {
            cout << "NO\n";
            return;
        }

        st.erase(it);
        if (locked != -1) {
            st.insert(locked);
            locked = -1;
        }

        if (x - need > 0) {
            locked = x - need;
        }
        m--;
    }

    if (st.size() > 0 || locked != -1) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
    }
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
