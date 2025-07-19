#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

const int MAX_N = 32;

// [i-th digit from right][generates_carry][needs_carry] = number of combinations
ll combinations[MAX_N][2][2];

// 1567C: Carrying Conundrum
void solve()
{
    string N; cin >> N;
    int n = N.size();
    reverse(N.begin(), N.end());

    for (int i = 0; i < n; ++i) {
        int target_digit = N[i] - '0';
        for (int j = 0; j <= 1; j++) {
            int goal = j*10 + target_digit;
            int without_carry = 0;
            int with_carry = 0;

            for (int d1 = 0; d1 <= min(9, goal); d1++) {
                for (int d2 = 0; d2 <= min(9, goal - d1); d2++) {
                    int carry = goal - d1 - d2;
                    if (carry < 0 || carry > 1) continue;
                    with_carry += carry;
                    without_carry += !carry;
                }
            }

            combinations[i][j][0] = without_carry;
            if (i >= 2 && max(combinations[i-2][1][0], combinations[i-2][1][1]) > 0) {
                combinations[i][j][1] = with_carry;
            }
        }
    }

    auto compute_mask = [&](int mask) {
        ll res = combinations[0][1 & mask][0];
        for (int i = 1; i < n; ++i) {
            bool out_carry = ((1 << i) & mask) != 0;
            bool in_carry = ((1 << (i-2)) & mask) != 0;

            if (i >= n-2) out_carry = 0;
            if (i <= 1) in_carry = 0;

            res *= combinations[i][out_carry][in_carry];
        }

        return res;
    };

    ll ans = compute_mask(0);
    int max_mask = (1 << (n-2)) - 1;
    for (int mask = 1; mask <= max_mask; mask++)
        ans += compute_mask(mask);

    cout << ans - 2 << '\n';
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
