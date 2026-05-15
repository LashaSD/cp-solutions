#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 1986E: Beautiful Array
void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> vec(n);
    for (int i = 0; i < n; ++i) {
        cin >> vec[i];
    }

    sort(vec.begin(), vec.end());
    map<int, vector<int>> mp;
    for (int x: vec) {
        mp[x % k].push_back(x);
    }

    int ans = 0;
    bool flag = n % 2 == 0;
    vector<int> pa, sa;
    for (auto it = mp.begin(); it != mp.end(); it++) {
        const vector<int>& v = it->second;
        // cerr << "MOD(" << it->first << "): ";
        // for (int x: v) {
        //     cerr << x << ' ';
        // }
        // cerr << '\n';

        int score = 0;
        for (size_t i = 0; i < v.size()-1; i += 2) {
            int a = v[i], b = v[i+1];
            score += (b - a) / k;
        }

        if (v.size() % 2 == 1) {
            if (flag) {
                cout << -1 << '\n';
                return;
            }
            flag = 1;
            if (v.size() == 1) continue;

            pa.resize(v.size(), 0);
            sa.resize(v.size(), 0);
            pa[0] = pa[1] = (v[1] - v[0]) / k;
            for (size_t i = 2; i < pa.size()-1; i += 2) {
                pa[i] = pa[i+1] = ((v[i+1] - v[i]) / k) + pa[i-1];
            }

            sa[v.size()-1] = sa[v.size() - 2] = (v[v.size() - 1] - v[v.size() - 2]) / k;
            for (size_t i = v.size() - 3; i >= 2; i -= 2) {
                sa[i] = sa[i-1] = ((v[i] - v[i-1]) / k) + sa[i+1];
            }

            score = LLONG_MAX;
            for (size_t i = 0; i < v.size(); i += 2) {
                int loc_score = 0;
                // cerr << "DBG: ";
                if (i > 0) {
                    // cerr << pa[i-1] << ' ';
                    loc_score += pa[i-1];
                }
                if (i < v.size()-1) {
                    // cerr << sa[i+1] << ' ';
                    loc_score += sa[i+1];
                }
                // cerr << '\n';
                score = min(score, loc_score);
            }

        }

        ans += score;
    }

    cout << ans << '\n';
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
