#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

int ask(const vector<int>& buf)
{
    cout << "? " << buf.size() << ' ';
    for (int x: buf)
        cout << x << ' ';
    cout << '\n';
    cout.flush();

    int ans;
    cin >> ans;
    return ans;
}

// 2159A. MAD Interactive Problem
void solve()
{
    int n; cin >> n;
    vector<int> vec(2*n);
    for (int i = 0; i < 2*n; ++i) {
        vec[i] = i+1;
    }

    vector<int> ans(2*n+1);

    vector<int> known;
    vector<int> buf;
    buf.push_back(vec[0]);
    for (int i = 1; i < 2*n; ++i) {
        buf.push_back(vec[i]);
        int num = ask(buf);
        if (num) {
            ans[vec[i]] = num;
            known.push_back(vec[i]);
            buf.pop_back();
        }
    }

    for (int i: buf) {
        known.push_back(i);
        int num = ask(known);
        ans[i] = num;
        known.pop_back();
    }

    cout << "! ";
    for (int i = 1; i <= 2*n; ++i) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
    cout.flush();
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
