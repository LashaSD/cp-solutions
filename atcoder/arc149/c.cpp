#include <algorithm>
#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

const int MAX_N = 1e4 + 5;
vector<vector<int>> ans(MAX_N, vector<int>(MAX_N));

void precompute()
{
    ans[0] = { 1, 3, 5 };
    ans[1] = { 8, 7, 9 };
    ans[2] = { 4, 2, 6 };

    for (int sq = 4; sq <= MAX_N; ++sq) {
        int sq_l = ((sq - 1) * (sq - 1)) + 1;
        int sq_r = sq * sq;
        int diff = sq_r - sq_l + 1;

        vector<int> row, col;
        for (int i = 0; i < diff; ++i) {
            int x = sq_l + i;
            if (x % 2 == 0) {
                row.push_back(x);
            } else {
                col.push_back(x);
            }
        }

        // reserve special numbers
        int e = 2, o = 2;

        for (int i = 0; i < row.size(); ++i) {
            if (row.back() % 3 == 0)
                if (row[row.size() - 2] % 3 == 0) break;

            int x = row[i];
            if (x % 3 == 0) {
                row.erase(row.begin() + i);
                row.push_back(x);
            }
        }

        for (int i = 0; i < col.size(); ++i) {
            if (col.back() % 3 == 0)
                if (col[col.size() - 2] % 3 == 0) break;

            int x = col[i];
            if (x % 3 == 0) {
                col.erase(col.begin() + i);
                col.push_back(x);
            }
        }

        if (sq == 5) {
            row.erase(find(row.begin(), row.end(), 20));
            row.push_back(20);
            col.erase(find(col.begin(), col.end(), 25));
            col.push_back(25);
        }

        if (sq == 6) {
            int i = find(row.begin(), row.end(), 36) - row.begin();
            int j = find(row.begin(), row.end(), 26) - row.begin();
            swap(row[i], row[j]);
        }

        // row
        for (int i = 0; i < row.size(); ++i) {
            ans[sq-1][i] = row[i];
        }

        for (int i = 0; i < col.size(); ++i) {
            ans[i][sq-1] = col[i];
        }
    }
}

// ARC149C: Avoid Prime Sum
void solve()
{
    int n; cin >> n;
    int N = n*n;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%4d ", ans[i][j]);
        }
        printf("\n");
    }
}

int T = 1;
int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    precompute();

    // cin >> T;
    while(T--)
        solve();
    return 0;
}
