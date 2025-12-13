#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2055D: Scarecrow
void solve()
{
    int n, k, l;
    cin >> n >> k >> l;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    int pos = k, t = 2*a[0];
    int i = 0;
    while (pos < l) {
        if (i == n-1) {
            // move straight to l
            if (t % 2 == 1) {
                t++, pos++;
            }

            t += 2*(l - pos);
            break;
        }

        // check if pos has a valid mover
        i++;
        if (a[i] <= pos) {
            int p = min(pos, a[i] + (t/2));
            pos = p + k;
        }

        if (a[i] > pos) {
            int p = max(pos, a[i] - (t/2));
            if (p == pos) {
                pos += k;
                continue;;
            }

            p -= t%2;

            // both multiplied by two
            int mid = p - pos;
            int mx_dt = 2*(l - pos);
            int delta = min(mid, mx_dt);
            //cerr << "DBG: " << pos << ' ' << delta << ' ' << i << '\n';
            if (delta % 2 == 1) {
                pos += delta/2 + k + t%2;
                t += delta;
            } else {
                t += delta;
                pos += delta/2 + k;
            }
        }
    }

    cout << t << '\n';
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
