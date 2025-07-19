#include <algorithm>
#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

// 1506E: Restoring the Permutation
void solve()
{
    int n; cin >> n;
    vector<int> pref_max(n);
    for (int& a: pref_max)
        cin >> a;

    set<int> unused;
    for (int i = 1; i <= n; ++i) unused.insert(i);

    vector<int> vec(n, -1);
    vec[0] = pref_max[0];
    unused.erase(vec[0]);
    for (int i = 1; i < n; ++i) {
        if (pref_max[i] != pref_max[i-1]) {
            vec[i] = pref_max[i];
            unused.erase(vec[i]);
        }
    }

    vector<int> minimal = vec, maximal = vec;
    for (int& a: minimal) {
        if (a == -1) {
            auto it = unused.begin();
            a = *it;
            unused.erase(it);
        }
    }

    for (int i = 1; i <= n; ++i) unused.insert(i);
    for (int i: vec) {
        if (i != -1)
            unused.erase(i);
    }

    for (int i = 0; i < n; ++i) {
        if (vec[i] != -1) continue;

        int lim = pref_max[i];
        auto it = --unused.lower_bound(lim);
        maximal[i] = *it;
        unused.erase(it);
    }

    for (int i: minimal)
        cout << i << ' ';
    cout << '\n';

    for (int i: maximal)
        cout << i << ' ';
    cout << '\n';
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
