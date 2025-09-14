#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll

const int INF = 2e9;

// 2014G: Milky Days
void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    stack<pair<int, int>> st;
    vector<pair<int, int>> vec(n);
    for (auto& p: vec)
        cin >> p.first >> p.second;

    int ans = 0;
    vec.push_back({INF, 0});
    for (int i = 0; i < n; ++i) {
        int day = vec[i].first;
        int next_day = vec[i+1].first;

        st.push({day + k - 1, vec[i].second});
        int fill = 0;

        while (!st.empty() && day < next_day) {
            auto p = st.top();
            st.pop();

            int last_day = p.first;
            int reserve = p.second;

            if (fill > 0 && day <= last_day) {
                int diff = min(m - fill, reserve);
                reserve -= diff;
                fill += diff;
                if (fill == m) {
                    // cerr << "D: " << day << ' ' << reserve << ' ' << last_day << '\n';
                    day++;
                    ans++;
                    fill = 0;
                    st.push({last_day, reserve});
                }
                continue;
            }

            if (day > last_day || reserve == 0) continue; 
            
            int days = min({next_day - day, last_day - day + 1, reserve / m});
            day += days;
            ans += days;

            if (day <= last_day) {
                if (day < next_day) {
                    fill += reserve % m;
                } else {
                    st.push({last_day, reserve - m*days});
                }
            }
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
