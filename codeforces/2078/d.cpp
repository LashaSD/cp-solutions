#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

// 2078D: Scammy Game Ad
void solve()
{
    int n; cin >> n;
    // {op, num}
    using pci = pair<char, int>;
    vector<pair<pci, pci>> vec(n);
    for (int i = 0; i < n; ++i) {
        char op1; int x1;
        cin >> op1 >> x1;

        char op2; int x2;
        cin >> op2 >> x2;

        vec[i].first = { op1, x1 };
        vec[i].second = { op2, x2 };
    }

    ll a = 1, b = 1;
    ll sum = 0;
    ll reserve = 0;
    for (int i = 0; i < n; ++i) {
        auto ops = vec[i];
        auto op1 = ops.first;
        auto op2 = ops.second;

        char l = op1.first, r = op2.first;
        int x = op1.second, y = op2.second;

        bool rhs_is_greater = false;
        bool need_to_find_first_dillema = (l == '+' && r == '+') || (l == 'x' && r == 'x' && x == y);

        for (int j = i+1; j < n && need_to_find_first_dillema; ++j) {
            auto ops = vec[j];
            auto op1 = ops.first, op2 = ops.second;
            char l = op1.first, r = op2.first;
            int x = op1.second, y = op2.second;
            if (l == '+' && r == 'x') {
                rhs_is_greater = true;
                break;
            } else if (l == 'x' && r == '+') {
                rhs_is_greater = false;
                break;
            } else if (l == 'x' && r == 'x') {
                if (x == y) continue;

                if (x > y) {
                    rhs_is_greater = false;
                } else {
                    rhs_is_greater = true;
                }

                break;
            }
        }

        if (l == '+' && r == '+') {
            if (rhs_is_greater) {
                b += reserve;
            } else {
                a += reserve;
            }

            reserve = x + y;
        } else if (l == 'x' && r == '+') {
            a += reserve;

            reserve = (x - 1) * a + y;
        } else if (l == '+' && r == 'x') {
            b += reserve;

            reserve = x + (y - 1) * b;
        } else if (l == 'x' && r == 'x') {
            if (x > y) {
                rhs_is_greater = false;
            } else if (x < y) {
                rhs_is_greater = true;
            }

            if (rhs_is_greater) {
                b += reserve;
            } else {
                a += reserve;
            }

            reserve = (x - 1) * a + (y - 1) * b;
        }

        dbg(a, b);
        dbg(reserve);
    }

    cout << a + b + reserve << '\n';
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
