#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// ARC154B: New Place 
void solve()
{
    int n; cin >> n;
    string s1, s2;
    cin >> s1 >> s2;

    vector<int> f1(26);
    vector<int> f2(26);
    for (char c: s1) {
        f1[c-'a']++;
    }

    for (char c: s2) {
        f2[c-'a']++;
    }

    bool ok = true;
    for (int i = 0; i < 26; ++i) {
        if (f1[i] != f2[i]) {
            ok = false;
            break;
        }
    }

    if (!ok) {
        cout << -1 << '\n';
        return;
    }

    auto check = [&](int len) {
        if (len == n) return true;
        int current = len;
        for (int i = 0; i < n; ++i) {
            if (s2[i] == s1[current])
                current++;
            if (current == n) return true;
        }

        return false;
    };

    int l = 0, r = n;
    int ans = -1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (check(mid)) {
            r = mid-1;
            ans = mid;
        } else {
            l = mid+1;
        }
    }

    cout << ans << '\n';
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
