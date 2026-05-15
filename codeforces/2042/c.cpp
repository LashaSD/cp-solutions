#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2042C: Competitive Fishing
void solve()
{
    int n, k;
    cin >> n >> k;
    string s; cin >> s;

    vector<int> suff(n);
    suff[n-1] = (s[n-1] == '1' ? 1 : -1);
    for (int i = n-2; i >= 0; --i) {
        suff[i] = suff[i+1] + (s[i] == '1' ? 1 : -1);
    }

    vector<int> ordered(n);
    for (int i = 0; i < n; ++i)
        ordered[i] = i;

    sort(ordered.begin() + 1, ordered.end(), [&](int a, int b) {
        return suff[a] > suff[b];
    });

    int sum = 0;
    int cnt = 1;
    for (int i = 1; i < n; ++i) {
        int j = ordered[i];
        cnt++;
        sum += suff[j];
        if (sum >= k) {
            cout << cnt << '\n';
            return;
        }
    }

    cout << -1 << '\n';
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
