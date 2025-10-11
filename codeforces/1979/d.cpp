#include <iostream>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;
using ll = long long;

const int mod = 998244353;

#define int ll

int is_proper(string& s, int k) {
    int n = s.size();
    int chain = 1;
    for (int i = 1; i < n; ++i) {
        if (s[i] == s[i-1]) {
            chain++;
        } 

        if (s[i] != s[i-1] || i == n-1) {
            if (chain == k) {
                chain = 1;
            } else {
                if (s[i] == s[i-1]) {
                    if (chain < k) {
                        return i;
                    } else {
                        return i - k;
                    }
                } else {
                    if (chain < k) {
                        return i-1;
                    } else {
                        return i - k - 1;
                    }
                }
            }
        }
    }

    return -1;
}

// 1979D: Fixing a Binary String
void solve()
{
    int n, k; 
    cin >> n >> k;

    string s; cin >> s;
    n = s.size();

    int l = is_proper(s, k);
    if (l == -1) {
        int bcnt = 1;
        for (int i = 1; i < n; ++i) {
            if (s[i] != s[i-1]) {
                bcnt++;
            }
        }

        if (bcnt == 1) {
            cout << 1 << '\n';
        } else {
            cout << k * ((bcnt % 2) + 1) << '\n';
        }

        return;
    }


    //cerr << "DBG: " << l << '\n';
    string a = s.substr(0, l + 1);
    reverse(a.begin(), a.end());

    string b = "";
    if (l < n-1) {
        b = s.substr(l + 1, n - l - 1);
    }

    string c = b + a;
    bool ok = is_proper(c, k) == -1;
    if (ok) {
        cout << l + 1 << '\n';
    } else {
        cout << -1 << '\n';
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
