#include <algorithm>
#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

// 1709C: Recover an RBS
void solve()
{
    string s; cin >> s;
    int n = s.size();
    vector<int> vec(n);
    for (int i = 0; i < n; ++i) {
        int x = s[i] == '(' ? 1 : s[i] == ')' ? -1 : 0;
        vec[i] = x;
    }

    int sum = 0;
    for (int x: vec) {
        sum += x;
    }

    int marks = count(vec.begin(), vec.end(), 0);
    if (marks <= 1) {
        cout << "YES\n";
        return;
    }

    int opened = 0, closed = 0;
    if (sum < 0) opened = -sum;
    if (sum > 0) closed = sum;

    marks -= (opened + closed);
    opened += marks / 2;
    closed += marks / 2;

    int l = -1, r = -1;
    for (int i = 0, cnt = 0; i < n; ++i) {
        if (vec[i] == 0) cnt++;

        if (cnt == opened && l == -1) {
            l = i;
        }

        if (cnt == opened + 1 && r == -1) {
            r = i;
            break;
        }
    }

    for (int i = 0, cnt = 0; i < n; ++i) {
        if (vec[i] == 0) {
            cnt++;
            if (cnt <= opened)
                vec[i] = 1;
            else
                vec[i] = -1;
        }
    }

    if (l == -1 || r == -1) {
        cout << "YES\n";
        return;
    }

    vec[l] = -1;
    vec[r] = 1;
    vector<int> pref(n+1);
    for (int i = 1; i <= n; ++i) {
        pref[i] = pref[i-1] + vec[i-1];
    }

    for (int i = 1; i <= n; ++i) {
        if (pref[i] < 0) {
            cout << "YES\n";
            return;
        }
    }

    cout << "NO\n";
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
