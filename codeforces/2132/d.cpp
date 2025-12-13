#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

ll ans = 0, num = 0, rem = 0;
void g(int n)
{
    int len = 0, sz = 0;
    while (len < n) {
        sz++;
        int cnt = (9 * powl(10, sz-1)) * sz;
        if (len + cnt < n) {
            len += cnt;
            continue;
        }

        int i = (n - len + (sz - 1)) / sz;
        rem = (len + sz*i) - n;
        num = powl(10, sz-1) + (i-1);
        return;
    }
}

void f(int x) 
{
    int i = 0, p = 1;
    while (p <= x) {
        int lim = (x / p) % 10;
        int l = (x / p) / 10;
        int r = x % p;

        for (int d = 1; d <= 9; ++d) {
            int oc = 0;
            if (d == lim) {
                oc = ((r + 1) + l*p);
            } else if (d < lim) {
                oc = ((l + 1) * p);
            } else if (d > lim) {
                oc = (l * p);
            }

            ans += oc*d;
        }

        p *= 10;
        i++;
    }
}

// 2132D: From 1 to Infinity
void solve()
{
    ans = num = rem = 0;
    int t; cin >> t;

    g(t);
    if (num-1 >= 0)
        f(num-1);

    while (num > 0) {
        if (rem <= 0) {
            ans += num % 10;
        }

        rem--;
        num /= 10;
    }

    cout << ans << '\n';
}

// 123456790 8 

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
