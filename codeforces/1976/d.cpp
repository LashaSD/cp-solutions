#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 1976D: Invertible Bracket Sequences
void solve()
{
    string s; cin >> s;
    int n = s.size();
    s.insert(0, " ");

    vector<int> pref(n+1), inv_pref(n+1);
    for (int i = 1; i <= n; ++i) {
        pref[i] = pref[i-1] + (s[i] == '(' ? 1 : -1);
        inv_pref[i] = inv_pref[i-1] + (s[i] == '(' ? -1 : 1);
    }

    int nBit = 63 - __builtin_clzll(n);
    vector<vector<int>> rmq(n+1, vector<int>(nBit+1));
    for (int i = 1; i <= n; ++i) {
        rmq[i][0] = inv_pref[i];
    }

    for (int j = 1; j <= nBit; ++j) {
        int len = (1ll << j);
        for (int l = 1; l + (len/2) <= n; ++l) {
            rmq[l][j] = min(rmq[l][j-1], rmq[l+(len/2)][j-1]);
        }
    }

    auto query = [&](int l, int r) {
        int bit = 63 - __builtin_clzll(r - l + 1);
        return min(rmq[l][bit], rmq[r - (1ll << bit) + 1][bit]);
    };

    map<int, vector<int>> oc;
    for (int i = 1; i <= n; ++i) {
        oc[pref[i]].push_back(i);
    }

    int ans = 0;
    for (int l = 1; l <= n; ++l) {
        int maxR = -1;
        int tl = l, tr = n;
        while (tl <= tr) {
            int mid = tl + (tr - tl) / 2;
            if (query(l, mid) - inv_pref[l-1] + pref[l-1] >= 0) {
                tl = mid+1;
                maxR = mid;
            } else {
                tr = mid-1;
            }
        }

        const vector<int>& pos = oc[pref[l-1]];
        if (pos.size() == 0) {
            continue;
        }

        auto it_l = lower_bound(pos.begin(), pos.end(), l);
        auto it_r = upper_bound(pos.begin(), pos.end(), maxR);
        int cnt = it_r - it_l;
        if (cnt > 0) {
            ans += cnt;
        }
    }

    cout << ans << '\n';
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
