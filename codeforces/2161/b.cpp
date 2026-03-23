#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

int n;

const vector<pair<int, int>> offsets = {
    {1, 1},
    {-1, 1},
    {1, -1},
    {-1, -1},
};

bool match(const vector<string>& grid, const vector<string>& mask)
{
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == '#' && mask[i][j] == '-') {
                return false;
            }
        }
    }

    return true;
}

void staircase(int r, int c, vector<string>& out, int di, int dj)
{
    for (int i = r, j = c, f = 1; i >= 0 && j >= 0 && i < n && j < n; ) {
        out[i][j] = '+';
        if (f) i += di;
        else j += dj;
        f = !f;
    }

    for (int i = r, j = c, f = 1; i >= 0 && j >= 0 && i < n && j < n; ) {
        out[i][j] = '+';
        if (f) j -= dj;
        else i -= di;
        f = !f;
    }
}

const vector<pair<int, int>> box_offsets = {
    {0, 0},
    {0, 1},
    {1, 0},
    {1, 1},
};

void box(int r, int c, vector<string>& out)
{
    for (auto [di, dj]: box_offsets) {
        int r1 = r + di;
        int c1 = c + dj;
        if (r1 >= 0 && r1 < n && c1 >= 0 && c1 < n) {
            out[r1][c1] = '+';
        }
    }
}

// 2161B: Make Connected
void solve()
{
    cin >> n;
    vector<string> grid(n);
    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
    }

    int r = -1, c = -1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == '#') {
                r = i, c = j;
            }
        }
    }

    if (r == -1 && c == -1) {
        cout << "YES\n";
        return;
    }

    for (auto [di, dj]: offsets) {
        vector<string> mask(n, string(n, '-'));
        staircase(r, c, mask, di, dj);
        if (match(grid, mask)) {
            cout << "YES\n";
            return;
        }
    }

    for (auto [di, dj]: box_offsets) {
        di--;
        dj--;
        vector<string> mask(n, string(n, '-'));
        box(r + di, c + dj, mask);
        if (match(grid, mask)) {
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
