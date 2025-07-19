#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

typedef struct Box {
    int left, right, bottom, top;
} Box;

const int MAX_N = 1e6 + 5;
Box prefix[MAX_N];

// 1607E: E. Robot on the Board 1
void solve()
{
    int n, m;
    cin >> n >> m;

    string s; cin >> s;
    int N = s.size();
    Box current = {0};
    int x = 0, y = 0;
    int i = 0;
    for (char c: s) {
        if (c == 'L')
            x--;
        else if (c == 'R')
            x++;
        else if (c == 'U')
            y++;
        else if (c == 'D')
            y--;

        current.right = max(current.right, x);
        current.top = max(current.top, y);
        current.left = min(current.left, x);
        current.bottom = min(current.bottom, y);

        prefix[i] = current;
        i++;
    }

    pair<int, int> ans = {1, 1};
    for (int i = 0; i < N; ++i) {
        Box& box = prefix[i];
        int width = box.right - box.left + 1;
        int height = box.top - box.bottom + 1;
        if (height <= n && width <= m) {
            ans = { box.top + 1, (-box.left + 1) };
        } else {
            break;
        }
    }

    cout << ans.first << ' ' << ans.second << '\n';
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
