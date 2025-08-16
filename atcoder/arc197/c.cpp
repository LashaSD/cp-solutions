#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

#define int ll

const int MAX_N = 4e6 + 5;

vector<int> fenwick(MAX_N + 1, 0);

void add(int i, int x)
{
    for (; i < MAX_N; i += (i & -i)) {
        fenwick[i] += x;
    }
}

int pref(int r)
{
    int sum = 0;
    for (int i = r; i > 0; i -= (i & -i)) {
        sum += fenwick[i];
    }

    return sum;
}

int range(int l, int r) {
    return pref(r) - pref(l-1);
}

// ARC197C: Removal of Multiples
void solve()
{
    for (int i = 1; i <= MAX_N; ++i) {
        add(i, 1);
    }

    int q; cin >> q;
    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        if (a <= MAX_N && range(a, a) != 0) {
            for (int i = a; i <= MAX_N; i += a) {
                if (range(i, i) == 1)
                    add(i, -1);
            }
        }

        int l = 1, r = MAX_N;
        int pos = -1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            int order = pref(mid);
            if (order == b) {
                pos = mid;
                r = mid - 1;
            } else if (order < b) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }

        cout << pos << '\n';
    }
}

int T = 1;
int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // cin >> T;
    while(T--)
        solve();
    return 0;
}
