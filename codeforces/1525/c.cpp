#include <iostream>
#include <numeric>
#include <cassert>
#include <climits>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <map>

using namespace std;
using ll = long long;

#define int ll
vector<pair<int, char>> vec;
int M = -1;

int hittime(pair<int, char> a, pair<int, char> b)
{
    int x1 = a.first;
    int c1 = a.second;

    int x2 = b.first;
    int c2 = b.second;

    assert(x1 < x2);

    if (c1 == 'R' && c2 == 'L') {
        return (x2 - x1) / 2;
    } else if (c1 == 'R' && c2 == 'R') {
        return (M - x2) + (x2 - x1) / 2;
    } else if (c1 == 'L' && c2 == 'L') {
        return x1 + (x2 - x1) / 2;
    } else if (c1 == 'L' && c2 == 'R') {
        int mn = min(x1, M - x2);
        if (x1 > mn)
            a.first -= mn;
        else
            a.first = 0, a.second = 'R';

        if ((M - x2) > mn)
            b.first += mn;
        else
            b.first = M, b.second = 'L';

        return mn + hittime(a, b);
    }

    return 0;
}

void solve1(vector<int>& ans, vector<int>& v)
{
    int n = v.size();

    vector<int> st;
    for (int i = 0; i < n; ++i) {
        auto& p = vec[v[i]];
        char c = p.second;

        if (c == 'L' && st.size() > 0) {
            int j = st.back();
            auto& p1 = vec[v[j]];
            st.pop_back();

            //cerr << "JOIN: (" << p1.first << ", " << p1.second << ") ";
            //cerr << "(" << p.first << ", " << p1.second << ")\n";

            ans[v[i]] = hittime(p1, p);
            ans[v[j]] = hittime(p1, p);
        } else {
            st.push_back(i);
        }
    }

    for (int i = (int) st.size() - 1; (i - 1) >= 0; i -= 2) {
        int v1 = st[i], v2 = st[i-1];
        auto p = vec[v[v1]], p1 = vec[v[v2]];

        //cerr << "ST_JOIN: (" << p1.first << ", " << p1.second << ") ";
        //cerr << "(" << p.first << ", " << p1.second << ")\n";

        ans[v[v1]] = hittime(p1, p);
        ans[v[v2]] = hittime(p1, p);
    }
}

// 1525C: Robot Collisions
void solve()
{
    int n;
    cin >> n >> M;
    vec.clear();
    vec.resize(n);

    for (int i = 0; i < n; ++i) {
        cin >> vec[i].first;
    }

    for (int i = 0; i < n; ++i) {
        cin >> vec[i].second;
    }

    vector<int> v(n);
    iota(v.begin(), v.end(), 0);
    sort(v.begin(), v.end(), [&](int a, int b) {
        return vec[a].first < vec[b].first;
    });

    vector<int> ans(n, -1);

    vector<int> evens, odds;
    for (int i = 0; i < n; ++i) {
        int x = vec[v[i]].first;
        if (x % 2 == 0) {
            evens.push_back(v[i]);
        } else {
            odds.push_back(v[i]);
        }
    }

    //for (int i = 0; i < (int) odds.size(); ++i) {
    //    auto p = vec[odds[i]];
    //    cerr << "ODD: (" << p.first << ", " << p.second << ")\n";
    //}

    //for (int i = 0; i < (int) evens.size(); ++i) {
    //    auto p = vec[evens[i]];
    //    cerr << "EVEN: (" << p.first << ", " << p.second << ")\n";
    //}

    solve1(ans, evens);
    solve1(ans, odds);

    for (int i = 0; i < n; ++i) {
        cout << ans[i] << ' ';
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
