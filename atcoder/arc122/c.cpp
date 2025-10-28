#include <iostream>
#include <climits>
#include <cassert>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <map>

using namespace std;
using ll = long long;
using ull = unsigned long long;

#define int ll

const int maxF = 92;
vector<int> fib(maxF + 1);

// ARC122C: Calculator
void solve()
{
    fib[1] = 1;
    fib[2] = 1;
    for (int i = 3; i <= maxF; ++i) {
        fib[i] = fib[i-1] + fib[i-2];
    }

    int n; cin >> n;
    int k = INT_MAX;

    int f = 0;
    vector<pair<int, int>> add;
    for (int i = 1; i <= maxF; i += 2) {
        ll x = fib[i];

        if (x > n) break;
    
        int _k = i;
        ll _x = n - x;

        vector<pair<int, int>> _add;

        for (int j = 1; j <= i; ++j) {
            ull z = fib[i - j + 1];
            if (_x / z > 0) {
                _add.push_back(make_pair(j, _x / z));
            }
            _k += _x / z;
            _x = _x % z;
        }

        if (_k < k) {
            f = i;
            k = _k;
            add = _add;
        }
    }

    vector<int> ans = { 1 };
    reverse(add.begin(), add.end());
    int _f = 1;
    int x = 1, y = 0;
    bool toggle = false;
    while (true) {
        if (add.size() > 0 && add.back().first == _f) {
            int j = add.back().first;
            int num = add.back().second;
            int turn = j % 2 == 1 ? 1 : 2;
            for (int i = 0; i < num; ++i) {
                ans.push_back(turn);
                x += turn == 1;
                y += turn == 2;
            }

            add.pop_back();
        }

        if (_f == f) break;

        if (toggle) {
            ans.push_back(3);
            x = x + y;
        } else {
            ans.push_back(4);
            y = x + y;
        }
        _f++;
        toggle = !toggle;
    }

    assert(x == n);

    cout << ans.size() << '\n';
    for (int x: ans) {
        cout << x << '\n';
    }
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
