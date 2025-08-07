#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

// 1367D: Task On The Board
void solve()
{
    string s; cin >> s;
    int n; cin >> n;

    vector<int> b(n);
    for (int& x: b) cin >> x;

    sort(s.begin(), s.end());

    vector<int> indices; indices.reserve(n);
    string ans(n, ' ');
    int steps = 0;
    while (indices.size() != n) {
        vector<int> loc_index;

        for (int i = 0; i < n; ++i) {
            if (ans[i] != ' ') continue;

            int sum = 0;
            for (int index: indices) {
                sum += abs(i - index);
            }

            if (b[i] == sum) {
                loc_index.push_back(i);
            }
        }

        char c;
        int cnt = 0;
        while (cnt < loc_index.size()) {
            cnt = 0;
            c = s.back();
            while (!s.empty() && s.back() == c) {
                s.pop_back();
                cnt++;
            }
        }

        for (int index: loc_index) {
            ans[index] = c;
            indices.push_back(index);
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
