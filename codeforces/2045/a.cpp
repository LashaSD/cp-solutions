#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

// A. Scrambled Scrabble
void solve()
{
    string s; cin >> s;
    int v = 0, c = 0, y = 0;
    int n = 0, g = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == 'Y')
            y++;
        else if (s[i] == 'A' || s[i] == 'E' || s[i] == 'I' || s[i] == 'O' || s[i] == 'U')
            v++;
        else
            c++;

        if (s[i] == 'N')
            n++;
        else if (s[i] == 'G')
            g++;
    }

    int used_c = 0;

    // vowels consonants
    // cvc
    int cnt = min(v, c/2);
    v -= cnt;
    c -= 2*cnt;
    used_c = cnt*2;

    // y consonants
    // cyc
    cnt = min(y, c/2);
    y -= cnt;
    c -= cnt*2;
    used_c += cnt*2;

    // vowels y
    // yvy
    cnt = min(v, y/2);
    v -= cnt;
    y -= cnt*2;
    used_c += cnt*2;

    // y y
    // yyy
    // only count ys that we have to delete from the string
    c += y % 3;

    // replace single-letter consonants with ng consonants
    int ng = min(n, g);
    c = max(0, c - min(used_c, ng));
    cout << s.size() - v - c << '\n';
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
