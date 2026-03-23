#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2124D: Make a Palindrome
void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> a(n), f(n+1);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        f[a[i]]++;
    }

    int accum = f[1], x = 1;
    for (; x <= n && accum < k; x++, accum += f[x]);
    if (x == 1) {
        cout << "YES\n";
        return;
    }

    vector<int> pal;
    for (int i = 0; i < n; ++i) {
        if (a[i] < x) pal.push_back(i);
    }

    int m = pal.size();
    for (int i = 0; i < m/2; ++i) {
        if (a[pal[i]] != a[pal[m - i - 1]]) {
            cout << "NO\n";
            return;
        }
    }

    // now we have to choose which xs can stay
    int need = f[x] - (accum - k + 1);

    vector<int> l(n+1);
    int curr = 0;
    for (int i = 0; i < n; ++i) {
        if (a[i] < x) curr++;
        if (a[i] != x) continue;
        l[curr]++;
    }

    auto ok = [&](int need) {
        auto cl = l;
        if (need % 2 == 1 && m % 2 == 1) {
            // we have two odd frequency numbers
            return false;
        }

        if (need % 2 == 1) {
            if (cl[m/2] > 0) {
                cl[m/2]--;
                need--;
            } else {
                return false;
            }
        }

        for (int i = 0; i <= m/2 && need > 0; ++i) {
            if (i == m-i) {
                int cnt = cl[i] / 2;
                cl[i] -= 2*cnt;
                need -= 2*cnt;
            } else {
                int cnt = min(cl[i], cl[m-i]);
                cl[i] -= cnt;
                cl[m-i] -= cnt;
                need -= 2*cnt;
            }
        }

        return need <= 0;
    };

    bool yes = ok(need);
    if (f[x] >= (need + 1)) yes |= ok(need + 1);
    cout << (yes ? "YES\n" : "NO\n");
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
