#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// ARC138B: 01 Generation
void solve()
{
    int n; cin >> n;
    deque<int> dec;
    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        dec.push_back(x);
    }

    bool reversed = false;
    bool processed = false;
    do {
        processed = false;

        while (!dec.empty() && dec.back() == reversed) {
            dec.pop_back();
            processed = true;
        }

        if (!dec.empty() && dec.front() == reversed) {
            dec.pop_front();
            reversed = !reversed;
            processed = true;
        }
    } while (processed && !dec.empty());

    if (dec.empty()) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
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
