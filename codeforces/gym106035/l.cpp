#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// GYM106035L: Pills
int n = -1, t = -1, ans = -1;
void solve()
{
    if (n == -1) {
        cin >> n;
        cout << n << '\n';
        for (int i = 1; i <= n; ++i) {
            cout << i << ' ' << i << '\n';
        }
        cout.flush();
    }

    ll sum = 0;
    for (int i = 1; i <= n; ++i) {
        sum += 500*i;
    }

    if (t == -1) cin >> t;

    for (int i = 1; i <= n; ++i) {
        if (sum - 500*i + 501*i == t) {
            ans = i;
            //cout << "! " << i << '\n';
            //cout.flush();
            return;
        }
    }
}

void test()
{
    n = 100000;
    int x = 25000;
    ll sum = 0;
    for (int i = 1; i <= n; ++i) {
        sum += 500*i;
    }

    for (int x = 1; x <= n; ++x) {
        ll sum1 = sum - 500*x + 501*x;
        t = sum1;
        solve();
        if (ans != x) {
            cout << "ERROR\n";
            exit(1);
        }
    }
}

// 250250587 

int T = 1;
int32_t main(void)
{
    test();
    //solve();

    return 0;
}
