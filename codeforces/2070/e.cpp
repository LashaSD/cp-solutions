#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

struct FT {
    int n;
    vector<int> tree;
    FT(int _n): n(_n) {
        tree.resize(n+1);
    }

    int query(int i) const {
        int res = 0;
        for (; i >= 1; i -= (i & -i)) {
            res += tree[i];
        }
        return res;
    }

    void update(int i, int delta) {
        for (; i <= n; i += (i & -i)) {
            tree[i] += delta;
        }
    }
};

const int maxX = 1e6;

// 2070E: Game with Binary String
void solve()
{
    int n; cin >> n;
    string s; cin >> s;
    n = s.size();
    s.insert(s.begin(), ' ');

    const int maxsz = 2*maxX+1;
    vector<int> pref(n+1);
    vector<FT> vec(4, FT(maxsz));

    int c1 = 0, c0 = 0;
    for (int i = 1; i <= n; ++i) {
        c1 += (s[i] == '1');
        c0 += (s[i] == '0');
        pref[i] = 3*c1 - c0;
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int k = 0; k <= 3; ++k) {
            int rem = (i - k + 1 + 4) % 4;
            int x = k == 3 ? pref[i + 1] - 1 : pref[i + 1] + 2;
            int cnt_ft = vec[rem].query(maxsz) - vec[rem].query(maxX + x - 1);
            ans += cnt_ft;
        }

        vec[i % 4].update(maxX + pref[i], 1);
    }

    cout << ans << '\n';
}

int T = 1;
int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //cin >> T;
    while(T--)
        solve();

    return 0;
}
