#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll

int cnt = 1;

// 1950G: Shuffling Songs
void solve()
{
    int n; cin >> n;
    vector<pair<int, int>> vec(n);

    map<string, int> mp_a;
    map<string, int> mp_b;
    int id = 0;
    for (int i = 0; i < n; ++i) {
        string a, b;
        cin >> a >> b;

        if (mp_a[a] > 0) {
            vec[i].first = mp_a[a];
        } else {
            id++;
            vec[i].first = id;
            mp_a[a] = id;
        }

        if (mp_b[b] > 0) {
            vec[i].second = mp_b[b];
        } else {
            id++;
            vec[i].second = id;
            mp_b[b] = id;
        }
    }

    int max_mask = (1ll << 16) - 1;
    int ans = 1;

    vector<int> state(max_mask + 1, 0);
    vector<bool> dp(max_mask + 1, 0);
    for (int i = 0; i < n; ++i) {
        int mask = (1ll << i);
        dp[mask] = 1;
        state[mask] = mask;
    }

    for (int mask = 0; mask <= max_mask; mask++) {
        if (!dp[mask]) continue;

        int loc_mask = state[mask];
        for (int i = 0; i < n; ++i) {
            int bit = (1ll << i);
            if ((bit & mask) != 0) continue;

            for (int j = 0; j < n; ++j) {
                int loc_bit = (1ll << j);
                if ((loc_bit & loc_mask) == 0) continue;

                auto x = vec[i], y = vec[j];
                if (x.first == y.first || x.second == y.second) {
                    dp[mask | bit] = 1;
                    ans = max(ans, (ll) __builtin_popcountll(mask | bit));
                    state[mask | bit] |= bit;
                }
            }
        }
    }

    cout << n - ans << '\n';
}

int T = 1;
int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    cin >> T;
    while(T--) {
        solve();
        cnt++;
    }
    return 0;
}
