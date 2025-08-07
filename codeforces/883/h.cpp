#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

bool cmp(pair<char, int>& a, pair<char, int>& b) {
    return a.second < b.second;
}

// 883H: Palindromic Cut
void solve()
{
    int n; cin >> n;
    string s; cin >> s;

    vector<int> freaky(128);
    for (char c: s) {
        freaky[c - '0']++;
    }

    int odd_cnt = 0;
    for (int f: freaky) {
        if (f % 2 == 1) odd_cnt++;
    }

    auto ok = [&](int part_cnt) {
        int len = n / part_cnt;
        if (len % 2 == 1) {
            return odd_cnt <= part_cnt && (part_cnt - odd_cnt) % 2 == 0;
        } else {
            return odd_cnt == 0;
        }
    };

    int parts = n;
    for (int i = 1; i <= n; ++i) {
        if (n % i == 0 && ok(i)) {
            parts = i;
            break;
        }
    }

    vector<pair<int, char>> freaks;
    vector<char> odds;
    for (int i = 0; i < freaky.size(); ++i) {
        int f = freaky[i];
        char c = '0' + i;
        if (f > 1) {
            int even = ((f >> 1) << 1);
            freaks.push_back({even, c});
        }

        if (f % 2)
            odds.push_back(c);
    }

    int len = n / parts;
    bool extra = len % 2;
    int even_len = ((len >> 1) << 1);

    dbg(freaks);
    dbg(odds);

    while (extra && odds.size() != parts) {
        auto& freak = freaks.back();
        odds.push_back(freak.second);
        odds.push_back(freak.second);
        freak.first -= 2;
        if (freak.first == 0)
            freaks.pop_back();
    }

    vector<string> ans(parts, string(len, ' '));
    for (int i = 0; i < parts; ++i) {
        vector<pair<int, char>> s;
        int current = 0;

        if (freaks.empty()) {
            current++;
            s.push_back({1, odds.back()});
            odds.pop_back();
        }

        while (current != len) {
            auto& freak = freaks.back();
            int diff = even_len - current;
            int used = min(diff, freak.first);
            freak.first -= used;
            current += used;

            s.push_back({used, freak.second});
            if (freak.first == 0)
                freaks.pop_back();

            if (current == even_len) {
                if (extra) {
                    s.push_back({1, odds.back()});
                    odds.pop_back();
                    current++;
                }
            }
        }

        int l = 0, r = len - 1;
        for (auto [f, c]: s) {
            while (f > 0) {
                f -= 2;
                ans[i][l++] = ans[i][r--] = c;
            }
        }
    }

    cout << parts << '\n';
    for (string s: ans) {
        cout << s << ' ';
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
