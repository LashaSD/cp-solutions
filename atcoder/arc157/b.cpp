#include <algorithm>
#include <bits/stdc++.h>
#include <iterator>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

#define int ll

int build(string &s, int k) {
    int n = s.size();

    vector<int> bridges;
    int bridge = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'Y') {
            if (bridge != 0) {
                bridges.push_back(bridge);
            }
            bridge = 0;
        } else {
            bridge++;
            if (i == n-1) {
                bridges.push_back(bridge);
            }
        }
    }

    if (s[0] == 'X') bridges.erase(begin(bridges));
    if (s.back() == 'X' && !bridges.empty()) bridges.pop_back();

    int sum = count(begin(s), end(s), 'Y') + k;
    int sub = bridges.size() + 1;
    sort(begin(bridges), end(bridges));

    dbg(s);
    dbg(k);
    dbg(sum, sub);
    dbg(bridges);

    int accum = 0;
    for (int i: bridges) {
        accum += i;
        if (accum > k) break;
        sub--;
    }

    return max(0ll, sum - sub);
}

// ARC157B
void solve()
{
    int n, k;
    cin >> n >> k;
    string s; cin >> s;

    int x_cnt = count(begin(s), end(s), 'X');
    int y_cnt = count(begin(s), end(s), 'Y');
    if (x_cnt < k) {
        for (char& c: s) {
            c = (c == 'Y') ? 'X' : 'Y';
        }
        k = y_cnt - (k - x_cnt);
    }

    cout << build(s, k) << '\n';
}

int T = 1;
int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // cin >> T;
    while(T--)
        solve();
    return 0;
}
