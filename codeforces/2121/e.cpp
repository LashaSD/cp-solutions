#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

// 2121E: Sponsor of Your Problems
void solve()
{
    string l, r;
    cin >> l >> r;
    int n = l.size();

    int ans = 0;
    int idx = 0;
    while (idx < n && l[idx] == r[idx]) ans+=2, idx++;

    if (idx < n && r[idx] - l[idx] == 1) {
        ans++;
        int l_ans = ans, r_ans = ans;
        for (int i = idx+1; i < n; ++i) {
            if (l[i] < '9') {
                if (l[i] == '8' && r[i] == '9')
                    l_ans++;
                break;
            } else {
                l_ans += 1 + (r[i] == '9');
            }
        }

        for (int i = idx+1; i < n; ++i) {
            if (r[i] > '0') {
                if (r[i] == '1' && l[i] == '0')
                    r_ans++;
                break;
            } else {
                dbg("HERE");
                r_ans += 1 + (l[i] == '0');
            }
        }

        dbg(l_ans, r_ans);
        cout << min(l_ans, r_ans) << '\n';
    } else {
        cout << ans << '\n';
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
