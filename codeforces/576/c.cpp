#include <iostream>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

struct P {
    int x, y;
    void read() {
        cin >> x >> y;
    }
    bool operator<(const P& b) const {
        return make_pair(x, y) < make_pair(b.x, b.y);
    };
};

static inline bool cmp(const pair<P, int>& a, const pair<P, int>& b)
{
    return make_pair(a.xx.y, a.xx.x) < make_pair(b.xx.y, b.xx.x);
}

// 576C: Points on Plane
void solve()
{
    int n; cin >> n;
    vector<pair<P, int>> a(n);
    for (int i = 0; i < n; ++i) {
        a[i].xx.read();
        a[i].yy = i;
    }

    int k = 1e3;
    sort(a.begin(), a.end());
    vector<vector<pair<P, int>>> blocks;
    int blk = -1e4;
    for (int i = 0; i < n; ++i) {
        int x = a[i].xx.x;
        if (x > blk + k) {
            blk = x / k * k;
            blocks.emplace_back();
        }
        
        blocks.back().push_back(a[i]);
    }
    cerr << "HERE\n";

    vector<pair<P, int>> ans;
    for (int i = 0; i < (int) blocks.size(); ++i) {
        vector<pair<P, int>>& cur = blocks[i];
        sort(cur.begin(), cur.end(), cmp);
        ans.insert(ans.end(), cur.begin(), cur.end());
    }

    for (int i = 0; i < (int) ans.size(); ++i) {
        cout << ans[i].yy + 1 << ' ';
    }
    cout << '\n';
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
