#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second
using P = pair<int, int>;

const int MOD = 676767677;

// 2211C2: Equal Multisets (Hard Version)
void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }

    int inc = 1, start = k;
    for (int rep = 0; rep < 2; ++rep) {
        for (int i = start; i < n && i >= k; i += inc) {
            int x = a[i-k], y = b[i-k];
            bool ok = 1;
            if (x != a[i]) {
                if (y == -1) b[i-k] = y = x;

                if (b[i] == -1) b[i] = a[i];

                if (y != x || b[i] != a[i]) ok = 0;
            } else if (x == a[i]) {
                if (b[i] == -1) b[i] = y;

                if (y == -1) b[i-k] = y = b[i];

                if (y != b[i]) ok = 0;
            }

            if (!ok) {
                cout << "NO\n";
                return;
            }
        }

        start = n-1;
        inc = -1;
    }

    vector<int> fa(n+1), fb(n+1);
    for (int i = 0; i < k; ++i) {
        fa[a[i]]++;
        if (b[i] == -1) continue;
        fb[b[i]]++;
    }

    for (int i = 0; i < k; ++i) {
        if (b[i] == -1) continue;

        if (fb[b[i]] > fa[b[i]]) {
            cout << "NO\n";
            return;
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
