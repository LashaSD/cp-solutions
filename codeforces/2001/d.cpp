#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll

// 2001D: Longest Max Min Subsequence
void solve()
{
    int n; cin >> n;
    vector<int> vec(n);
    for (int& x: vec)
        cin >> x;

    vector<vector<int>> pos(n+1);
    for (int i = 0; i < n; ++i) {
        pos[vec[i]].push_back(i);
    }

    vector<pair<int, int>> last_pos;
    for (int x = 1; x <= n; ++x) {
        if (pos[x].size() > 0) {
            last_pos.push_back({pos[x].back(), x});
        }
    }

    sort(last_pos.begin(), last_pos.end());
    
    vector<bool> used(n+1, 0);
    set<pair<int, int>> st;

    vector<int> ans;
    int i = 0;
    int j = 0;
    int k = -1;
    while (ans.size() < last_pos.size()) {
        //cerr << "MAIN: \n";
        while (j < (int) last_pos.size() && used[last_pos[j].second]) j++;
        int y = last_pos[j].second;
        for (; i <= last_pos[j].first; ++i) {
            if (!used[vec[i]]) {
                //cerr << "    APPEND: " << vec[i] << '\n';
                st.insert({vec[i], i});
            }
        }

        j++;
        bool locked_y = false;

        while (k < i && st.size() > 0 && !locked_y) {
            bool is_odd = (ans.size() + 1) % 2;
            bool found = false;

            while (st.size() > 0 && !found) {
                int x = is_odd ? (--st.end())->first : st.begin()->first;
                auto it = st.lower_bound({x, k});
                if (it != st.end() && it->first == x) {
                    k = it->second;
                    //cerr << "        LOCKED: " << x << '\n';
                    used[x] = 1;
                    ans.push_back(x);
                    found = true;
                    if (x == y) locked_y = 1;
                }

                while (st.size() > 0) {
                    auto itt = is_odd ? --st.end() : st.begin();
                    if (itt->first == x) st.erase(itt);
                    else break;
                    //cerr << "        REMOVING\n";
                }
            }
        }
    }

    cout << ans.size() << '\n';
    for (int x: ans)
        cout << x << ' ';
    cout << '\n';
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
