#include <algorithm>
#include <bits/stdc++.h>
#include <cstring>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

// *
// **
const int OPEN_BOT = 0;

// **
// *
const int OPEN_TOP = 1;

// ***
// ***
const int FLAT = 2;

// ***
//  ***
const int FLAT_BOT = 3;

//  ***
// ***
const int FLAT_TOP = 4;

// **
//  *
const int CLOSE_BOT = 5;

//  *
// **
const int CLOSE_TOP = 6;

// 2022C: Gerrymandering
void solve()
{
    int n; cin >> n;
    vector<vector<bool>> vec(2, vector<bool>(n));
    vector<vector<int>> dp(n, vector<int>(7));
    for (int i = 0; i < 2; ++i) {
        string s; cin >> s;
        for (int j = 0; j < n; ++j)
            vec[i][j] = s[j] == 'A';
    }

     auto compute = [&](int i, int state) {
        switch (state) {
            case OPEN_BOT: {
                return (int) ((vec[0][i] + vec[1][i] + vec[1][i+1]) >= 2);
            } break;
            case OPEN_TOP: {
                return (int) ((vec[0][i] + vec[1][i] + vec[0][i+1]) >= 2);
            } break;
            case FLAT: {
                int top = (vec[0][i] + vec[0][i+1] + vec[0][i+2]) >= 2;
                int bot = (vec[1][i] + vec[1][i+1] + vec[1][i+2]) >= 2;
                return top + bot;
            } break;
            case FLAT_BOT: {
                int top = (vec[0][i] + vec[0][i+1] + vec[0][i+2]) >= 2;
                int bot = (vec[1][i+1] + vec[1][i+2] + vec[1][i+3]) >= 2;
                return top + bot;
            } break;
            case FLAT_TOP: {
                int top = (vec[0][i+1] + vec[0][i+2] + vec[0][i+3]) >= 2;
                int bot = (vec[1][i] + vec[1][i+1] + vec[1][i+2]) >= 2;
                return top + bot;
            } break;
            case CLOSE_BOT: {
                return (int) ((vec[0][i] + vec[0][i+1] + vec[1][i+1]) >= 2);
            } break;
            case CLOSE_TOP: {
                return (int) ((vec[1][i] + vec[1][i+1] + vec[0][i+1]) >= 2);
            } break;
        }

        return -1;
     };

    for (int j = OPEN_BOT; j <= FLAT; ++j) {
        dp[0][j] = compute(0, j);
    }

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j <= 6; ++j) {
            switch (j) {
                case FLAT:
                    if (i > n-2) continue;
                case OPEN_BOT: case OPEN_TOP: {
                    if (i % 3 != 0) continue;
                    int val = compute(i, j);
                    dp[i][j] = max(dp[i][j], val + max({dp[i-3][FLAT], dp[i-2][CLOSE_TOP], dp[i-2][CLOSE_BOT]}));
                } break;
                case FLAT_BOT:
                    if (i >= n-2) continue;
                case CLOSE_BOT: {
                    if (i % 3 != 1) continue;
                    int val = compute(i, j);
                    int mx = 0;
                    if (i > 3) mx = dp[i-3][FLAT_BOT];
                    dp[i][j] = max(dp[i][j], val + max({mx, dp[i-1][OPEN_BOT]}));
                } break;
                case FLAT_TOP:
                    if (i >= n-2) continue;
                case CLOSE_TOP: {
                    if (i % 3 != 1) continue;
                    int val = compute(i, j);
                    int mx = 0;
                    if (i > 3) mx = dp[i-3][FLAT_TOP];
                    dp[i][j] = max(dp[i][j], val + max({mx, dp[i-1][OPEN_TOP]}));
                } break;
            }
        }
    }

    // for (int j = 0; j < n; ++j) {
    //     for (int i = 0; i <= CLOSE_TOP; ++i)
    //         cerr << dp[j][i] << ' ';
    //     cerr << '\n';
    // }
    // cerr << '\n';

    int ans = 0;
    for (int i = n-3; i < n; ++i) {
        for (int j = 0; j <= 6; ++j) {
            ans = max(ans, dp[i][j]);
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
