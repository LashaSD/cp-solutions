#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2123F: Minimize Fixed Points
void solve()
{
    int n; cin >> n;
    vector<int> vec(n+1);
    vec[1] = 1;

    vector<int> pr;
    vector<int> lp(n+1);
    for (int i = 2; i <= n; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
        }

        for (int j = 0; i * pr[j] <= n; ++j) {
            lp[pr[j] * i] = pr[j];
            if (pr[j] == lp[i]) break;
        }
    }

    reverse(pr.begin(), pr.end());
    vector<int> temp;
    for (int p: pr) {
        temp.clear();
        for (int j = p; j <= n; j += p) {
            if (vec[j] == 0)
                temp.push_back(j);
        }

        if (temp.size() == 1) {
            vec[p] = p;
            continue;
        }

        for (int j = 1; j < (int) temp.size(); ++j) {
            vec[temp[j-1]] = temp[j];
        }
        vec[temp.back()] = temp.front();
    }

    for (int i = 1; i <= n; ++i) {
        cout << vec[i] << ' ';
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
