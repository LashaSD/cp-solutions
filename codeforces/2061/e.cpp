#include <iostream>
#include <cassert>
#include <climits>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <list>
#include <chrono>

using namespace std;
using ll = long long;

#define int ll

// 2061E: Kevin and And
void solve()
{
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> a(n), b(m);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    for (int i = 0; i < m; ++i) {
        cin >> b[i];
    }

    int maxMask = (1ll << m) - 1;
    vector<vector<int>> dp(n, vector<int>(m + 1));
    for (int i = 0; i < n; ++i) {
        dp[i][0] = a[i];
        for (int mask = 0; mask <= maxMask; ++mask) {
            int c = a[i];

            if (mask & (1 << 0)) c &= b[0];
            if (mask & (1 << 1)) c &= b[1];
            if (mask & (1 << 2)) c &= b[2];
            if (mask & (1 << 3)) c &= b[3];
            if (mask & (1 << 4)) c &= b[4];
            if (mask & (1 << 5)) c &= b[5];
            if (mask & (1 << 6)) c &= b[6];
            if (mask & (1 << 7)) c &= b[7];
            if (mask & (1 << 8)) c &= b[8];
            if (mask & (1 << 9)) c &= b[9];

            int cnt = __builtin_popcountll(mask);
            dp[i][cnt] = max(dp[i][cnt], a[i] - c);
        }
    }

    // cerr << double(clock() - start) / CLOCKS_PER_SEC << '\n';

    for (int i = 0; i < n; ++i) {
        vector<int> pd(m+1);
        pd[1] = dp[i][1];
        for (int j = 2; j <= m; ++j) {
            pd[j] = dp[i][j] - dp[i][j-1];
        }

        for (int j = 0; j <= m; ++j) {
            dp[i][j] = pd[j];
        }
    }

    vector<int> pt(n, 1);

    set<pair<int, int>> st;
    for (int i = 0; i < n; ++i) {
        st.insert({-dp[i][pt[i]], i});
    }

    int delta = 0;
    while (k > 0) {
        auto it = st.begin(); 

        if (it == st.end()) {
            cout << "FORCE_WA\n";
            cout.flush();
            return;
        }

        int val = it->first;
        int idx = it->second;

        st.erase(it);
        pt[idx]++;
        if (pt[idx] <= m) {
            st.insert({-dp[idx][pt[idx]], idx});
        }
        delta += -val;

        k--;
    }

    int sum = 0;
    for (int x: a) {
        sum += x;
    }

    cout << sum - delta << '\n';
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
