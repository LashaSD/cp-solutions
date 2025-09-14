#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// 1500A: Going Home
void solve()
{
    int n; cin >> n;
    vector<int> vec(n);
    for (int& x: vec)
        cin >> x;

    vector<vector<pair<int, int>>> diff(3e6 + 1);
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            int a = i;
            int b = j;
            if (vec[a] > vec[b]) swap(a, b);

            int d = vec[b] - vec[a];

            pair<int, int> index = {-1, -1};

            for (auto p: diff[d]) {
                if (p.first == a || p.first == b || p.second == a || p.second == b) {
                    continue;
                }

                index = p;
                break;
            }

            if (diff[d].size() == 0) {
                diff[d].push_back({a, b});
            } else if (index.first != -1 && index.second != -1) {
                int x1 = index.second + 1;
                int y1 = a + 1;
                int x2 = index.first + 1;
                int y2 = b + 1;

                cout << "YES\n";
                cout << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << '\n';
                return;
            }
        }
    }

    cout << "NO\n";
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
