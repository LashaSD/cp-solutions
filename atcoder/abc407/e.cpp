#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll

// ABC407E: Most Valuable Parentheses
void solve()
{
    int n; cin >> n;
    n *= 2;
    vector<int> vec(n);
    for (int& x: vec)
        cin >> x;

    set<pair<int, int>> st;
    for (int i = 1; i < n-1; ++i) {
        st.insert({vec[i], i});
    }
    
    vector<int> p(n);
    p[0] = 1;
    p[n-1] = -1;

    int cnt = 0;
    int half = (n-2) / 2;
    for (auto [x, idx]: st) {
        cnt++;
        if (idx == 0 || idx == n-1) continue;

        p[idx] = cnt <= half ? -1 : 1;
    }

    set<pair<int, int>> open, closed;
    for (int i = 0; i < n; ++i) {
        if (p[i] == 1) {
            open.insert({vec[i], i});
        }
    }

    int ans = 0;
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        //cerr << "DBG_I: " << i << '\n';
        //for (int i = 0; i < n; ++i) {
        //    cerr << p[i] << ' ';
        //}
        //cerr << '\n';

        if (p[i] == 1) {
            open.erase({vec[i], i});
            ans += vec[i];
        } else {
            closed.insert({vec[i], i});
        }

        if (sum + p[i] < 0) {
            if (open.size() == 0) {
                cerr << "PIZDEC: " << i << '\n';
                exit(1);
            }

            auto cl_it = --closed.end();
            auto op_it = open.begin();

            int a = cl_it->first;
            int b = op_it->first;

            ans += a;
            
            //cerr << "ANS_DEL: " << b << '\n';
            //cerr << "ANS_ADD: " << a << '\n';

            p[cl_it->second] = 1;
            p[op_it->second] = -1;

            closed.erase(cl_it);
            open.erase(op_it);

            sum++;
        } else {
            sum += p[i];
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
