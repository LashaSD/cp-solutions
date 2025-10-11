#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll

// 1978E: Computing Machine
void solve()
{
    int n; cin >> n;
    string s, t;
    cin >> s >> t;

    vector<bool> aturn(n), bturn(n);

    string s1 = s, t1 = t;
    for (int i = 0; i < n - 2; ++i) {
        if (s[i] == '0' && s[i] == s[i + 2] && t[i + 1] == '0') {
            t1[i + 1] = '1';
            bturn[i + 1] = 1;
        }
    }

    for (int i = 0; i < n - 2; ++i) {
        if (t1[i] == '1' && t1[i] == t1[i + 2] && s[i + 1] == '0') {
            s1[i + 1] = '1';
            aturn[i + 1] = 1;
        }
    }

    vector<int> pref(n+1);

    for (int i = 1; i <= n; ++i) {
        pref[i] = pref[i-1] + (s1[i-1] == '1');
    }

    int q; cin >> q;
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        l--, r--;

        if (l == r) {
            cout << (s[l] == '1') << '\n';
            continue;
        }

        int sum = pref[r + 1] - pref[l];
        int sub = 0;
        set<int> ind = {l, l + 1, r - 1, r};
        for (int j: ind) {
            if (!aturn[j]) continue;

            if (j - 1 < l || j + 1 > r) {
                sub++;
                continue;
            }

            if ((bturn[j - 1] && j == (l+1)) || (bturn[j + 1] && j == (r - 1))) {
                sub++;
                continue;
            }
        }

        cout << sum - sub << '\n';
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
