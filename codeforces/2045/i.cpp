#include <bits/stdc++.h>

using namespace std;
using ll = long long;

static const int MAX_N = 3e5;
static int vec[MAX_N] = {0};
static pair<int, int> queries[MAX_N] = {{0, 0}};
static int freaky[MAX_N+1] = {0};
static int f[MAX_N+1] = {0};
int block_size = 0;

bool cmp(pair<int, int>& a, pair<int, int>& b)
{
    int index_a = a.first / block_size;
    int index_b = b.first / block_size;
    if (index_a == index_b)
        return a.second < b.second;

    return index_a < index_b;
}

// 2045I: Microwavable Subsequence
void solve()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        cin >> vec[i];

    ll sum = 0;
    int q_n = 0;
    for (int i = 0; i < n; ++i) {
        int x = vec[i];
        if (freaky[x] == 0) {
            sum += m - 1;
        } else {
            queries[q_n] = {freaky[x] + 1, i};
            q_n++;
        }

        freaky[x] = i+1;
    }

    block_size = sqrt(n);
    sort(queries, queries + q_n, cmp);
    
    int l = 0, r = -1;
    int distinct = 0;
    for (int i = 0; i < q_n; ++i) {
        auto p = queries[i];
        int tl = p.first - 1;
        int tr = p.second - 1;

        while (l > tl) {
            l--;
            int x = vec[l];
            if (f[x] == 0)
                distinct++;
            f[x]++;
        }

        while (r < tr) {
            r++;
            int x = vec[r];
            if (f[x] == 0)
                distinct++;
            f[x]++;
        }

        while (l < tl) {
            int x = vec[l];
            if (f[x] == 1)
                distinct--;
            f[x] = max(0, f[x]-1);
            l++;
        }

        while (r > tr) {
            int x = vec[r];
            if (f[x] == 1)
                distinct--;
            f[x] = max(0, f[x]-1);
            r--;
        }

        sum += distinct;
    }

    cout << sum << '\n';
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
