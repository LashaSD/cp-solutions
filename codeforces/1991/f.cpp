#include <iostream>
#include <functional>
#include <cassert>
#include <climits>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <map>

using namespace std;
using ll = long long;

#define int ll

vector<vector<int>> perms;

void precompute()
{
    set<vector<int>> _perms;

    vector<int> perm = {1, 1, 1, 2, 2, 2};
    _perms.insert(perm);
    while (next_permutation(perm.begin(), perm.end())) {
        vector<int> cp = perm;
        _perms.insert(cp);
    }

    for (auto p: _perms) {
        perms.push_back(p);
    }
}

static inline int triangle_count(const vector<int>& v)
{
    int n = v.size();
    int cnt = 0;
    for (int i = 0; i < n - 2; i++) {
        if (v[i] + v[i+1] > v[i+2]) {
            cnt++;
            i += 2;
        }
    }

    return cnt;
}

static inline bool scramble_check(const vector<int>::iterator begin)
{
    for (const auto& perm: perms) {
        int a[3], b[3];
        int i = 0, j = 0;
        auto it = begin;
        for (int k = 0; k < 6; ++k, it++) {
            if (perm[k] == 1) a[i++] = *it;
            if (perm[k] == 2) b[j++] = *it;
        }

        if (a[0] + a[1] > a[2] && b[0] + b[1] > b[2]) {
            return true;
        }
    }

    return false;
}

// 1991F: Triangle Formation
void solve()
{
    int threshold = 50;

    int n, q; 
    cin >> n >> q;

    vector<int> vec(n);
    for (int& x: vec)
        cin >> x;

    for (int qq = 0; qq < q; ++qq) {
        int l, r;
        cin >> l >> r;
        l--, r--;

        if (r - l + 1 >= threshold) {
            cout << "YES\n";
            continue;
        }

        vector<int> buf(vec.begin() + l, vec.begin() + r + 1);
        sort(buf.begin(), buf.end());

        int m = buf.size();

        if (triangle_count(buf) >= 2) {
            cout << "YES\n";
            continue;
        }

        bool ok = false;
        for (int i = 0; i < m - 5; ++i) {
            if (scramble_check(buf.begin() + i)) {
                ok = true;
                break;
            }
        }

        cout << (ok ? "YES\n": "NO\n");
    }
}

int T = 1;
int32_t main(void)
{
    precompute();

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // cin >> T;
    while(T--)
        solve();

    return 0;
}
