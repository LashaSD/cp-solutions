#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

int query(int x)
{
    cout << "? " << x + 1 << '\n';
    cout.flush();
    int t; cin >> t;
    return t;
}

// 2108D: Needle in a Numstack
void solve()
{
    int n, k;
    cin >> n >> k;
    if (n == 2*k) {
        cout << "! " << k << ' ' << k << '\n';
        cout.flush();
        return;
    } 

    vector<int> a(k), b(k);
    for (int i = 0; i < k; ++i) {
        a[i] = query(i);
    }

    // 0 1 2 3 | 0 1
    // ------
    // 0 1 2 3 
    for (int i = n-k; i < n; ++i) {
        b[i % k] = query(i);
    }

    vector<int> d;
    for (int i = 0; i < k; ++i) {
        if (a[i] != b[i])
            d.push_back(i);
    }

    if (d.size() == 0) {
        cout << "! -1\n";
        cout.flush();
        return;
    }

    // [1, 2, 3, ..., k][k + 1, k + 2, ..., 2k]

    int l = d.front(), r = d.front() + (((n - 1 - d.front()) / k * k));
    int edge = d.front();
    while (r - l > k) {
        int mid = l + (r - l) / k / 2 * k;
        if (query(mid) == a[d.front()]) {
            edge = mid;
            l = mid;
        } else {
            r = mid;
        }
    }

    l = 0, r = d.size() - 1;
    int j = -1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        int offset = d[mid];
        if (query(edge - d[0] + offset) == a[d[mid]]) {
            j = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    int apos = max(edge - d[0] + d[j], k - 1);

    int bpos;
    if (j + 1 < (int) d.size()) {
        bpos = min(edge - d[0] + d[j+1], n - k);
    } else {
        bpos = min(edge + k, n - k);
    }

    if (apos + 1 != bpos) {
        cout << "! -1\n";
        cout.flush();
        return;
    }

    cout << "! " << apos + 1 << ' ' << n - bpos << '\n';
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
