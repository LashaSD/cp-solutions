#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll

int head(vector<int>& p, int u)
{
    if (p[u] == u) return u;
    return p[u] = head(p, p[u]);
}

bool merge(vector<int>& p, int u, int v)
{
    u = head(p, u);
    v = head(p, v);
    p[u] = v;
    return u != v;
}

// 1946D: Birthday Gift
void solve()
{
    int n, m; 
    cin >> n >> m;
    vector<int> vec(n);
    for (int& x: vec)
        cin >> x;

    int comp_cnt = n;
    vector<int> p(n);
    for (int i = 0; i < n; ++i) 
        p[i] = i;

    int max_bit = 31;
    int ans = -1;
    for (int j = max_bit; j >= 0; --j) {
        int bit = (1ll << j);
        int m_bit = m & bit;

        vector<int> c_p = p;
        int c_comp_cnt = comp_cnt;

        int alone = -1;
        int bit_cnt = 0;
        for (int i = 0; i < n; ++i) {
            int y = vec[i];
            int y_bit = bit & y;
            if (y_bit != 0) {
                bit_cnt++;
                if (alone >= 0) {
                    if (merge(c_p, alone, i)) c_comp_cnt--;
                    alone = -1;
                } else {
                    alone = i;
                }
            } else if (alone >= 0) {
                if (merge(c_p, alone, i)) c_comp_cnt--;
            }
        }

        if (m_bit == 0) {
            if (bit_cnt % 2 == 1) break;
            p = c_p;
            comp_cnt = c_comp_cnt;
        } else {
            if (alone == -1) {
                ans = max(ans, c_comp_cnt);
            }
        }

        if (j == 0) {
            ans = max(ans, comp_cnt);
        }
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
