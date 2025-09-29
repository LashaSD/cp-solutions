#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll

void add(vector<int>& tree, int i, int x)
{
    int n = tree.size() - 1;
    for (; i <= n; i += (i & -i)) {
        tree[i] += x;
    } 
}

int range(vector<int>& tree, int i)
{
    int result = 0;
    for (; i > 0; i -= (i & -i)) {
        result += tree[i];
    }
    return result;
}

// 1896E: Permutation Sorting
void solve()
{
    int n; cin >> n;
    vector<int> vec(n);
    for (int& x: vec)
        cin >> x;

    vector<bool> mark(2*n+1);

    vector<pair<int, int>> qqs(2*n+1);

    for (int i = 1; i <= n; ++i) {
        int x = vec[i-1];
        if (i == x) continue;
        if (i < x) {
            qqs[x].first = i+1;
            qqs[x].second = x;
        } else {
            mark[x] = 1;
            x += n;

            qqs[x].first = i+1;
            qqs[x].second = n;
        }
    }

    vector<int> pos(2*n+1);
    for (int i = 0; i < n; ++i) {
        int x = vec[i];
        if (mark[x]) {
            pos[x + n] = i+1;
        } else {
            pos[x] = i+1;
        }
    }

    vector<int> tree(2*n+1);
    vector<int> ans(n+1);

    for (int x = 1; x <= n; ++x) {
        if (pos[x] == 0) {
            ans[x] += x - range(tree, x-1);
            continue;
        }

        if (vec[x-1] == x) {
            add(tree, pos[x], 1);
            continue;
        }

        auto [l, r] = qqs[x];
        //cerr << "DBG_1: " << x << ' ' << l << ' ' << r << '\n';
        ans[x] += (r - l + 1) - (range(tree, r) - range(tree, l-1));

        add(tree, pos[x], 1);
    }

    for (int x = 1; x <= n; ++x) {
        if (pos[x + n] == 0) continue;

        auto [l, r] = qqs[x + n];
        //cerr << "DBG_2: " << x << ' ' << l << ' ' << r << '\n';
        ans[x] += (r - l + 1) - (range(tree, r) - range(tree, l-1));

        add(tree, pos[x + n], 1);
    }

    for (int x = 1; x <= n; ++x) {
        cout << ans[x] << ' ';
    }
    cout << '\n';
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
