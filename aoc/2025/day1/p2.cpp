#include <bits/stdc++.h>

using namespace std;

signed main()
{
    string s;
    int ans = 0;
    int current = 50;
    while (cin >> s) {
        bool plus = s[0] == 'R';
        string num(s.begin() + 1, s.end());
        int x = stoi(num);
        int nxt = current + (plus ? 1 : -1) * x;
        int dx = 0;

        if (current < nxt) {
            dx = nxt / 100 - current / 100;
        } else {
            while (nxt <= 0) nxt += 100, current += 100;
            dx = (current - 1) / 100 - (nxt - 1) / 100;
        }

        ans += dx;
        current = nxt % 100;
    }

    cout << ans << '\n';
}
