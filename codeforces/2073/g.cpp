#include <iostream>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2073G: Corrupted File 
void solve()
{
    int n, m;
    cin >> n >> m;
    string s1, s2;
    cin >> s1 >> s2;
    n = s1.size();
    m = s2.size();

    vector<pair<int, int>> a, b;
    for (int i = 0; i < n; ++i) {
        if (i == 0 || s1[i] != s1[i-1]) {
            a.emplace_back(make_pair(s1[i] - '0', 0));
        }
        a.back().yy++;
    }

    for (int i = 0; i < m; ++i) {
        if (i == 0 || s2[i] != s2[i-1]) {
            b.emplace_back(make_pair(s2[i] - '0', 0));
        }
        b.back().yy++;
    }

    if (a.front().xx == 0 && b.front().xx == 1) {
        cout << "no\n";
        return;
    }

    // nabozari edge case
    if (a.front().xx == 1 && b.front().xx == 1 && a.front().yy < b.front().yy) {
        cout << "no\n";
        return;
    }

    if (a.back().xx == 0 && b.back().xx == 1) {
        cout << "no\n";
        return;
    }

    if (a.back().xx == 1 && b.back().xx == 1 && a.back().yy < b.back().yy) {
        cout << "no\n";
        return;
    }

    if (a.size() > 1 && b.size() == 1 && b.front().xx == 1) {
        cout << "no\n";
        return;
    }

    int i = 0, j = 0;
    int in = a.size(), jn = b.size();
    while (j < jn) {
        int cnt = 0;
        while (i < in) {
            if (a[i].xx != b[j].xx) {
                i++;
                continue;
            }

            if (a[i].xx == 1) {
                cnt = max(cnt, a[i].yy);
            } else if (a[i].xx == 0) {
                cnt += a[i].yy;
            }

            if (cnt >= b[j].yy) break;
            i++;
        }

        if (i == in) {
            cout << "no\n";
            return;
        }

        i++, j++;
    }

    cout << "yes\n";
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
