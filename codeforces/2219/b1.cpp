#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <cstdint>
#include <set>
#include <algorithm>
#include <functional>
#include <map>

#define assert(v) do { if (!(v)) { *(int*)0 = 0; } } while (0)

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

int n;

int query(int l, int r)
{
    if (l > r || r - l + 1 == n) {
        return 0;
    }

    if (l == r) {
        return 1;
    }

    cout << "? " << r - l + 1 << ' ';
    for (int i = l; i <= r; ++i) {
        cout << i << ' ';
    }
    cout << '\n';
    cout.flush();
    int q; cin >> q;
    return q;
}

int binary(int cnt)
{
    int l = 1, r = n;
    int save = -1;
    while (l <= r) {
        int x, y;

        int mid = l + (r - l) / 2;
        int a = query(1, mid);
        int b = query(mid+1, n);

        if (a == b) {
            int lena = mid;
            int lenb = n - mid;
            if (lena % 2 == a % 2) {
                x = 0, y = 3;
            } else {
                x = 3, y = 0;
            }
        } else if (a > b) {
            x = 1, y = 2;
        } else if (a < b) {
            x = 2, y = 1;
        }

        if (x >= cnt) {
            save = mid;
            r = mid-1;
        } else {
            l = mid+1;
        }
    }

    return save;
}

// 2219B1: Unique Values (Easy version)
void solve()
{
    cin >> n;
    n = 2*n+1;

    int t1 = -1, t2 = -1, t3 = 1;
    t1 = binary(1);
    t2 = binary(2);
    t3 = binary(3);
    cout << "! " << t1 << ' ' << t2 << ' ' << t3 << '\n';
    cout.flush();
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


