#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

// D - Logical Filling
void solve()
{
    int n, k;
    cin >> n >> k;
    string s; cin >> s;

    for (int i = 0; i < n; ++i) {
        if (s[i] == 'o') {
            if (i > 0 && s[i-1] == '?')
                s[i-1] = '.';
            if (i < n-1 && s[i+1] == '?')
                s[i+1] = '.';
            k--;
        }
    }

    if (k == 0) {
        for (int i = 0; i < n; ++i) {
            if (s[i] == '?')
                s[i] = '.';
        }
    }

    vector<pair<int, int>> ranges;

    bool chain = false;
    int l = 0;
    for (int r = 0; r < n; ++r) {
        if (s[r] != '?' && chain) {
            chain = false;
            ranges.push_back({l, r-1});
            int siz = r - l;
            k -= (siz + 1) / 2;
        }

        if (s[r] == '?' && !chain) {
            chain = true;
            l = r;
        }

        if (r == n - 1 && chain && s[r] == '?') {
            int siz = r - l + 1;
            ranges.push_back({l, r});
            k -= (siz + 1) / 2;
        }
    }

    if (k == 0) {
        for (pair<int, int>& range : ranges) {
            int l = range.first;
            int r = range.second;
            if ((r - l + 1) % 2 == 1) {
                s[l] = 'o';
                for (int it = l+1; it <= r; it++) {
                    s[it] = (s[it-1] == '.' ? 'o' : '.');
                }
            }
        }
    }

    cout << s << '\n';
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
