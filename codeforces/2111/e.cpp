#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// 2111E: Changing the String
void solve()
{
    int n, q;
    cin >> n >> q;
    string s; cin >> s;

    const int OP_BA = 0;
    const int OP_CA = 1;
    const int OP_BC = 2;
    const int OP_CB = 3;

    vector<set<int>> ops(4);
    for (int i = 0; i < q; ++i) {
        char x, y;
        cin >> x >> y;

        if (x == 'b' && y == 'a') {
            ops[OP_BA].insert(i);
        }

        if (x == 'c' && y == 'a') {
            ops[OP_CA].insert(i);
        }

        if (x == 'b' && y == 'c') {
            ops[OP_BC].insert(i);
        }

        if (x == 'c' && y == 'b') {
            ops[OP_CB].insert(i);
        }
    }

    for (int i = 0; i < n; ++i) {
        if (s[i] == 'a') continue;

        if (s[i] == 'c') {
            if (ops[OP_CA].size() > 0) {
                s[i] = 'a';
                ops[OP_CA].erase(ops[OP_CA].begin());
            } else if (ops[OP_CB].size() > 0) {
                s[i] = 'b';
                auto it = ops[OP_CB].begin();

                auto it1 = ops[OP_BA].lower_bound(*it);
                if (it1 != ops[OP_BA].end()) {
                    s[i] = 'a';
                    ops[OP_BA].erase(it1);
                }

                ops[OP_CB].erase(it);
            }

            continue;
        }

        if (s[i] == 'b') {
            if (ops[OP_BA].size() > 0) {
                s[i] = 'a';
                ops[OP_BA].erase(ops[OP_BA].begin());
            } else if (ops[OP_BC].size() > 0 && ops[OP_CA].size() > 0) {
                auto it = ops[OP_BC].begin();
                auto it1 = ops[OP_CA].lower_bound(*it);
                if (it1 != ops[OP_CA].end()) {
                    ops[OP_BC].erase(it);
                    ops[OP_CA].erase(it1);
                    s[i] = 'a';
                }
            }
        } 
    }

    cout << s << '\n';
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
