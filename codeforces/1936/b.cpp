#include <iostream>
#include <cassert>
#include <climits>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <map>

using namespace std;
using ll = long long;

#define int ll

// 1936B: Pinball
void solve()
{
    int n; cin >> n;
    string s; cin >> s;
    n = (int) s.size();

    // l = >
    // r = <
    vector<int> cntl(n+1), cntr(n+1);
    for (int i = 1; i <= n; ++i) {
        cntl[i] = cntl[i-1] + (s[i-1] == '>');
        cntr[i] = cntr[i-1] + (s[i-1] == '<');
    }

    vector<int> suml(n+1), sumr(n+1);
    for (int i = 1; i <= n; ++i) {
        suml[i] = suml[i-1] + (s[i-1] == '>' ? i : 0);
        sumr[i] = sumr[i-1] + (s[i-1] == '<' ? i : 0);
    }

    vector<int> idxr(n+1), idxl(n+1);
    for (int i = 1; i <= n; ++i) {
        if (s[i-1] == '<') {
            idxr[cntr[i]] = i;
        } else {
            idxl[cntl[i]] = i;
        }
    }

    vector<int> ans(n);
    for (int i = 0; i < n; ++i) {
        int a = cntl[i];
        int b = cntr[n] - cntr[i + 1];

        bool going_left = false;
        if (a < b || (s[i] == '<' && a <= b)) {
            going_left = true;
        }

        int dl = 0, dr = 0;
        if (going_left == (s[i] == '<')) {
            if (s[i] == '<' ) {
                dl = dr = a;
            } else {
                dl = dr = b;
            }
        } else {
            if (s[i] == '<') {
                dl = b + 1;
                dr = b;
            } else {
                dl = a;
                dr = a + 1;
            }
        }

        int sa = 0, sb = 0, sc = 0;
        if (going_left) {
            sa = suml[i];
            int j = idxr[cntr[i + 1] + dr];
            sb = sumr[j] - sumr[i+1];
            sc = i + 1;
        } else {
            sb = sumr[n] - sumr[i + 1];
            int j = idxl[cntl[i] - dl];
            sa = suml[i] - suml[j];
            sc = n - i;
        }

        // cerr << "DBG: " << dl << ' ' << dr << ' ' << sa << ' ' << sb << ' ' << sc << '\n';
        ans[i] = (2 * sb - 2 * dr * (i + 1)) + (2 * dl * (i + 1) - 2 * sa) + sc;
    }

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
