#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2114G: Build an Array 
void solve()
{
    int n, k;
    cin >> n >> k;

    vector<int> a(n+2);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    vector<int> p(n+1), s(n+2);
    for (int i = 1; i <= n; ++i) {
        int l = a[i-1];
        int x = a[i];

        bool gate = 0;
        for (int j = 0; j <= 30; ++j) {
            int y = (1ll << j);
            if (l > 0 && x % l == 0 && x / l == y) {
                gate = 1;
                break;
            }
        }

        for (int j = 31; j >= 0; --j) {
            int y = (1ll << j);
            if (x % y == 0) {
                int w = x / y;
                int z = gate ? y - (2*l / w) + 1 : y;
                p[i] = p[i-1] + z;
                break;
            }
        }
    }

    for (int i = n; i >= 1; --i) {
        int r = a[i+1];
        int x = a[i];

        bool gate = 0;
        for (int j = 0; j <= 30; ++j) {
            int y = (1ll << j);
            if (r > 0 && x % r == 0 && x / r == y) {
                gate = 1;
                break;
            }
        }

        for (int j = 31; j >= 0; --j) {
            int y = (1ll << j);
            if (x % y == 0) {
                int w = x / y;
                int z = gate ? y - (2*r / w) + 1 : y;
                s[i] = s[i+1] + z;
                break;
            }
        }
    }

    int mx = 0;
    for (int i = 1; i <= n; ++i) {
        int loc = 0;
        for (int j = 31; j >= 0; --j) {
            int y = (1ll << j);
            if (a[i] % y == 0) {
                loc = y;
                break;
            }
        }

        mx = max(mx, (p[n] - p[i]) + (s[1] - s[i]) + loc);
    }
    //cerr << "MAX: " << mx << '\n';

    cout << (mx >= k ? "YES\n" : "NO\n");
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
