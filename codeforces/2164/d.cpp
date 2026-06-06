#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <cstdint>
#include <set>
#include <algorithm>
#include <assert.h>
#include <functional>
#include <map>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2164D: Copy String
void solve()
{
    int n, k;
    cin >> n >> k;
    string s, t;
    cin >> s >> t;
    vector<vector<int>> pos(32);
    for (int i = 0; i < n; ++i) {
        int id = s[i] - 'a';
        pos[id].push_back(i);
    }

    vector<pair<int, int>> ops;

    int bound = n-1;
    for (int i = n-1; i >= 0; --i) {
        if (t[i] == s[i] && i <= bound) continue;

        int x = t[i] - 'a';
        int right_most = -1;
        vector<int> &st = pos[x];
        while (st.size() > 0 && (st.back() > bound || st.back() > i)) {
            st.pop_back();
        }

        if (st.size() == 0) {
            cout << -1 << '\n';
            return;
        }

        if (st.back() != bound) {
            ops.push_back({st.back(), i});
            bound = st.back();
        }
    }

    vector<string> ans;
    while (ans.size() < k) {
        const string &old_s = ans.size() == 0 ? s : ans.back();
        string new_s = old_s;
        bool op_done = 0;
        for (int k = 0; k < (int)ops.size(); ++k) {
            auto [i, j] = ops[k];
            if (i == j) continue;
            op_done = 1;

            new_s[i+1] = old_s[i];
            ops[k].xx++;
        }

        if (!op_done) {
            break;
        }

        ans.push_back(move(new_s));
    }

    bool all_done = 1;
    for (auto [i, j]: ops) {
        all_done &= i == j;
    }

    if (!all_done) {
        cout << -1 << '\n';
        return;
    }

    cout << ans.size() << '\n';
    for (const string &ss: ans) {
        cout << ss << '\n';
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
