#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

const char LEFT = '<';
const char RIGHT = '>';
const char DOWN = 'v';
const char UP = '^';

void solve()
{
    int n, m; cin >> n >> m;
    string rows, cols; cin >> rows >> cols;

    char top = rows[0], bottom = rows[n-1], left = cols[0], right = cols[m-1];

    bool ok = false;
    ok |= (top == RIGHT && right == DOWN && bottom == LEFT && left == UP);
    ok |= (top == LEFT && left == DOWN && bottom == RIGHT && right == UP);

    cout << (ok ? "YES\n" : "NO\n");
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
