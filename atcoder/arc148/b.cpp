#include <bits/stdc++.h>

using namespace std;
using ll = long long;

string inverse(const string s)
{
    string res;
    for (int i = s.size() - 1; i >= 0; --i) {
        if (s[i] == 'p')
            res.push_back('d');
        else
            res.push_back('p');
    }
    return res;
}

// ARC148B: dp
void solve()
{
    int n; cin >> n;
    string s; cin >> s;
    int l = 0;
    while (l < n && s[l] != 'p') l++;
    int r = l;
    for (int i = l+1; i < n; ++i) {
        // compare [l, r] to [l, i]
        string s1 = inverse(s.substr(l, r-l+1)) + s.substr(r+1, i-r);
        string s2 = inverse(s.substr(l, i-l+1));
        if (s2 <= s1) {
            r = i;
        }
    }

    for (int i = 0; i < l; ++i) {
        cout << s[i];
    }
    if (l < n) {
        for (int i = r; i >= l; --i) {
            cout << (s[i] == 'p' ? 'd' : 'p');
        }
    }
    for (int i = r+1; i < n; ++i) {
        cout << s[i];
    }
    cout << '\n';
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
