#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll

// ABC381F: 1122 Subsequence
void solve()
{
    int n; cin >> n;
    vector<int> vec(n);
    for (int& x: vec)
        cin >> x;

    // closest[x][i] = closest occurence of x starting from i (inclusive)
    vector<vector<int>> closest(21, vector<int>(n+1));
    for (int x = 1; x <= 20; ++x) {
        closest[x][n] = -1;
        for (int i = n-1; i >= 0; --i) {
            if (vec[i] == x) {
                closest[x][i] = i;
            } else {
                closest[x][i] = closest[x][i+1];
            }
        }
    }

    int max_mask = (1ll << 20) - 1;
    vector<vector<int>> masks(21, vector<int>());
    for (int mask = 0; mask <= max_mask; ++mask) {
        int s = __builtin_popcountll(mask);
        masks[s].push_back(mask);
    }

    vector<int> pos(max_mask + 1, LLONG_MAX);
    vector<vector<bool>> dp(21, vector<bool>(max_mask + 1));

    int ans = 0;
    for (int mask: masks[1]) {
        int x = (63 - __builtin_clzll(mask)) + 1;
        if (x == 0) {
            cerr << bitset<12>(mask) << '\n';
        }
        int cl = closest[x][closest[x][0] + 1];
        if (cl != -1) {
            pos[mask] = min(pos[mask], cl);
            dp[1][mask] = 1;
            ans = 1;
        }
    }

    for (int s = 2; s <= 20; ++s) {
        for (int mask: masks[s]) {
            for (int i = 0; i < 20; ++i) {
                int bit = (1ll << i);
                if ((bit & mask) == bit) {
                    int loc_mask = mask ^ bit;

                    if (dp[s-1][loc_mask]) {
                        int x = (63 - __builtin_clzll(bit)) + 1;
                        int cl1 = closest[x][pos[loc_mask] + 1];
                        int cl2 = closest[x][cl1 + 1];
                        if (cl1 >= 0 && cl2 >= 0) {
                            //cerr << "OK: " << bitset<12>(mask) << ' ' << x << '\n';
                            dp[s][mask] = 1;
                            pos[mask] = min(pos[mask], cl2);
                            ans = max(ans, s);
                        }
                    }
                }
            }
        }
    }

    cout << 2*ans << '\n';
}

int T = 1;
int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //cin >> T;
    while(T--)
        solve();
    return 0;
}
