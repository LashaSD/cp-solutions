#include <algorithm>
#include <bits/stdc++.h>
#include <cassert>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

// 2103C: Median Splits
void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> vec(n);
    for (int i = 0; i < n; ++i)
        cin >> vec[i];

    // diff: cnt(K) - cnt(X)
    vector<int> p_diff(n);

    p_diff[0] = vec[0] <= k ? 1 : -1;
    for (int i = 1; i < n; ++i) {
        p_diff[i] = p_diff[i-1] + (vec[i] <= k ? 1 : -1);
    }

    vector<int> s_diff(n);
    s_diff[n-1] = (vec[n-1] <= k) ? 1 : -1;
    for (int i = n-2; i >= 0; --i) {
        s_diff[i] = (s_diff[i+1] + (vec[i] <= k ? 1 : -1));
    }

    multiset<int> all_p_set, all_s_set;
    for (int i = 0; i < n; ++i) {
        all_p_set.insert(p_diff[i]);
        all_s_set.insert(s_diff[i]);
    }

    multiset<int> pref_set = all_p_set, suff_set = all_s_set;

    dbg(pref_set);
    for (int l = 0; l < n; ++l) {
        pref_set.erase(pref_set.find(p_diff[l]));
        suff_set.erase(suff_set.find(s_diff[l]));

        bool l_ok = p_diff[l] >= 0;
        if (!l_ok) continue;

        if (suff_set.lower_bound(0) != suff_set.end() || pref_set.lower_bound(p_diff[l]) != pref_set.end()) {
            cout << "YES\n";
            return;
        }
    }

    pref_set = all_p_set, suff_set = all_s_set;

    for (int r = n-1; r >= 1; --r) {
        pref_set.erase(pref_set.find(p_diff[r]));
        suff_set.erase(suff_set.find(s_diff[r]));

        bool r_ok = s_diff[r] >= 0;
        if (!r_ok) continue;

        if (pref_set.lower_bound(0) != pref_set.end() || suff_set.lower_bound(s_diff[r]) != suff_set.end()) {
            cout << "YES\n";
            return;
        }
    }

    dbg(p_diff);
    dbg(s_diff);

    cout << "NO\n";
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
