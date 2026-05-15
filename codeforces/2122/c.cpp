#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second
using P = pair<int, int>;

// 2122C: Manhattan Pairs
void solve()
{
    int n; cin >> n;
    vector<P> vec(n);
    vector<int> xs(n), ys(n);
    for (int i = 0; i < n; ++i) {
        cin >> vec[i].xx >> vec[i].yy;
        xs[i] = vec[i].xx;
        ys[i] = vec[i].yy;
    }

    sort(xs.begin(), xs.end());
    sort(ys.begin(), ys.end());

    // xmp[x] = one based index of unused x in sorted array of xs
    map<int, int> xmp, ymp;
    for (int i = 0; i < n; ++i) {
        if (xmp[xs[i]] == 0)
            xmp[xs[i]] = i+1;

        if (ymp[ys[i]] == 0)
            ymp[ys[i]] = i+1;
    }

    // a --
    // b ++
    // c +-
    // d -+
    vector<int> a, b, c, d;
    for (int i = 0; i < n; ++i) {
        int nx, ny;
        // one based
        nx = xmp[vec[i].xx]++;
        ny = ymp[vec[i].yy]++;

        if (nx <= n/2 && ny <= n/2) {
            a.push_back(i + 1);
        } else if (nx > n/2 && ny > n/2) {
            b.push_back(i + 1);
        } else if (nx > n/2 && ny <= n/2) {
            c.push_back(i + 1);
        } else if (nx <= n/2 && ny > n/2) {
            d.push_back(i + 1);
        }
    }

    for (int i = 0; i < (int)a.size(); ++i) {
        cout << a[i] << ' ' << b[i] << '\n';
    }

    for (int i = 0; i < (int)c.size(); ++i) {
        cout << c[i] << ' ' << d[i] << '\n';
    }
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
