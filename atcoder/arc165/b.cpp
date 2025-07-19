#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;

using ll = long long;

// ARC165: b
void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> vec(n);
    for (int i = 0; i < n; ++i) {
        int num; cin >> num;
        vec[i] = num;
    }

    int chain = 1, mx_chain = 1;
    for (int i = 1; i < n; ++i) {
        if (vec[i] > vec[i-1]) {
            chain++;
        } else {
            chain = 1;
        }
        mx_chain = max(mx_chain, chain);
    }

    if (mx_chain >= k) {
        for (int num: vec)
            cout << num << ' ';
        cout << '\n';
        return;
    }

    set<int> s;
    int l = n-k;
    int r = n-1;
    for (int i = l; i <= r; ++i) {
        s.insert(vec[i]);
    }

    vector<bool> lower(n), higher(n);
    int index = l;
    for (int num: s) {
        if (vec[index] != num) break;
        index++;
    }

    for (int i = l; i <= r; ++i) {
        if (i == index) continue;
        if (vec[i] < vec[index]) lower[i] = 1;
        if (vec[i] > vec[index]) higher[i] = 1;
    }

    int it = l;
    while ((it-1) >= 0 && vec[it] > vec[it-1]) {
        it--;
    }

    while ((l-1) >= 0) {
        int lowest = *s.begin();

        s.erase(vec[r]);
        if (lowest < vec[l-1]) break;
        s.insert(vec[l-1]);

        r--;
        l--;
    }

    vector<int> vec1 = vec, vec2 = vec;
    sort(vec1.begin() + l, vec1.begin() + l + k);
    sort(vec2.begin() + it, vec2.begin() + it + k);

    vector<int>& ans = vec1;
    for (int i = 0; i < n; ++i) {
        if (vec1[i] > vec2[i])
            break;
        else if (vec1[i] < vec2[i]) {
            ans = vec2;
            break;
        }
    }

    for (int num: ans)
        cout << num << ' ';
    cout << '\n';
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
