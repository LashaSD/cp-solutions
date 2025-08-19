#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

#define int ll

const string NAREK = "narek";
const int INF = 1e9;

pair<int, int> sim(string& s, int start)
{
    int index = start;
    int score = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == NAREK[index]) {
            index = (index + 1) % 5;
            score++;
        } else if (find(NAREK.begin(), NAREK.end(), s[i]) != NAREK.end()) {
            score--;
        }
    }

    return { score, index };
}

// 2005C: Lazy Narek
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<string> vec(n);
    for (string& s: vec)
        cin >> s;

    vector<int> dp(5, -INF);
    dp[0] = 0;
    for (int i = 0; i < n; ++i) {
        string& s = vec[i];
        vector<int> loc(5, -INF);
        for (int j = 0; j < 5; ++j) {
            auto res = sim(s, j);
            loc[res.second] = max(loc[res.second], dp[j] + res.first);
        }

        for (int j = 0; j < 5; ++j) {
            if (loc[j] != -INF) {
                dp[j] = max(dp[j], loc[j]);
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < 5; ++i) {
        ans = max(ans, dp[i] - 2*i);
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
