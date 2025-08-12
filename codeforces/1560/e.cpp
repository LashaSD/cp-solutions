#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

// 1560E: Polycarp and String Transformation
void solve()
{
    string s; cin >> s;
    int n = s.size();

    vector<int> g_freaky(26, 0);
    vector<int> last_pos(26, 0);
    for (int i = 0; i < n; ++i) {
        g_freaky[s[i] - 'a']++;
        last_pos[s[i] - 'a'] = i + 1;
    }

    vector<pair<int, char>> ops;
    for (int i = 0; i < 26; ++i) {
        char c = 'a' + i;
        if (last_pos[i] > 0) {
            ops.push_back({last_pos[i] - 1, c});
        }
    }

    sort(ops.begin(), ops.end());
    dbg(ops);

    vector<int> freaky(26, 0);
    int len = 0;
    for (int i = 0; i < 26; ++i) {
        int index = -1;
        for (int j = 0; j < ops.size(); ++j) {
            if (ops[j].second == i + 'a') {
                index = j;
                break;
            }
        }

        if (index == -1) continue;

        pair<char, int> op = ops[index];
        int c = op.second;
        int f = g_freaky[c - 'a'];

        if (f % (index + 1) != 0) {
            cout << -1 << '\n';
            return;
        }

        freaky[c - 'a'] = f / (index + 1);
        len += f / (index + 1);
    }

    string s_ops;
    for (int i = 0; i < ops.size(); i++)
        s_ops.push_back(ops[i].second);

    int idx = 0;
    vector<bool> blacklist(26);
    auto op_it = ops.begin();
    int len_cnt = 0, current_len = len;
    for (int i = 0; i < n; ++i) {
        while (blacklist[s[idx] - 'a'])
            idx = (idx + 1) % len;

        len_cnt++;
        if (len_cnt == current_len) {
            len_cnt = 0;
            current_len -= freaky[op_it->second - 'a'];
            blacklist[op_it->second - 'a'] = 1;
            op_it++;
        }

        if (s[idx] != s[i]) {
            cout << -1 << '\n';
            return;
        }

        idx = (idx + 1) % len;
    }

    cout << s.substr(0, len) << ' ' << s_ops << '\n';
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
