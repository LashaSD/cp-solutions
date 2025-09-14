#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// 1729F: Kirei and the Linear Function
void solve()
{
    string s; cin >> s;
    int w, m;
    cin >> w >> m;

    vector<int> oc[9];
    
    int n = s.size();
    vector<int> pref(n+1);
    for (int i = 0; i < n; ++i) {
        pref[i+1] = pref[i] + s[i] - '0';
    }

    for (int i = 0; i <= n-w; ++i) {
        int sum = pref[i + w] - pref[i];
        oc[sum % 9].push_back(i);
        //cout << "DBG: " << i << ' ' << sum%9 << '\n';
    }

    // ((x * c) + y) % 9 = k
    // (x%9 * c%9) + y%9 = k
    // (x_mod * c_mod) + y_mod = k
    // l_mod + y_mod = k
    auto check = [&](int x_mod, int y_mod) {
        pair<int, int> loc_ans = {-1, -1};
        if (x_mod != y_mod) {
            if (oc[x_mod].size() > 0 && oc[y_mod].size() > 0) {
                loc_ans.first = oc[x_mod].front() + 1;
                loc_ans.second = oc[y_mod].front() + 1;
            }
        } else {
            if (oc[x_mod].size() > 1) {
                loc_ans.first = oc[x_mod][0] + 1;
                loc_ans.second = oc[x_mod][1] + 1;
            }
        }

        return loc_ans;
    };

    for (int i = 0; i < m; ++i) {
        int l, r, k;
        cin >> l >> r >> k;
        int c = pref[r] - pref[l-1];
        int c_mod = c % 9;
        pair<int, int> ans = {-1, -1};
        for (int j = 0; j < 9; ++j) {
            for (int x = 0; x < 9; ++x) {
                if ((x * c_mod) % 9 != j) continue;
                int y_mod = (9 + (k - j)) % 9;
                pair<int, int> loc_ans = check(x, y_mod);
                if (loc_ans != make_pair(-1, -1)) {
                    if (ans == make_pair(-1, -1) || loc_ans < ans) {
                        ans = loc_ans;
                    }
                }
            }
        }

        cout << ans.first << ' ' << ans.second << '\n';
        cout.flush();
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
