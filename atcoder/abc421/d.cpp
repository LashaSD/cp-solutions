#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll

const int INF = LLONG_MAX / 2;

pair<bool, int> min_inters(pair<int, int> p, char pd, pair<int, int> q, char qd) {
    if (p.second == q.second) {
        if ((p.first < q.first && (pd != 'R' || qd != 'L')) || 
            (q.first < p.first && (pd != 'L' || qd != 'R'))) 
            return {false, 0};

        int len = abs(p.first - q.first) - 1;
        return {len % 2 == 1, (len + 1) / 2};
    }

    if (p.first == q.first) {
        if ((p.second < q.second && (pd != 'D' || qd != 'U')) || 
            (q.second < p.second && (pd != 'U' || qd != 'D'))) 
            return {false, 0};

        int len = abs(q.second - p.second) - 1;
        return {len % 2 == 1, (len + 1) / 2};
    }

    if (p.first > q.first) {
        swap(p, q);
        swap(pd, qd);
    }

    if (p.second < q.second)
        if (!((pd == 'R' && qd == 'U') || (pd == 'D' && qd == 'L'))) 
            return {false, 0}; 

    if (p.second > q.second)
        if (!((pd == 'R' && qd == 'D') || (pd == 'U' && qd == 'L')))
            return {false, 0};

    int dx = abs(p.first - q.first);
    int dy = abs(p.second - q.second);
    return {dx == dy, dx};
}

int intersections(pair<int, int> p, char pd, pair<int, int> q, char qd, int x)
{
    if (pd == qd || p == q)
        return (pd == qd && p == q ? x : 0);

    auto mn = min_inters(p, pd, q, qd);
    if (mn.first && mn.second <= x) return 1;

    return 0;
}

// ABC421D: RLE Moving
void solve()
{
    int x, y;
    int x1, y1;

    cin >> y >> x;
    cin >> y1 >> x1;

    int n; cin >> n;
    int m, l;
    cin >> m >> l;

    vector<pair<char, int>> t_moves(m), a_moves(l);

    for (int i = 0; i < m; ++i) {
        cin >> t_moves[i].first >> t_moves[i].second;
    }

    for (int i = 0; i < l; ++i) {
        cin >> a_moves[i].first >> a_moves[i].second;
    }

    int curr_move = 0;
    int t = 0, a = 0;
    int t_sum = 0, a_sum = 0;
    int ans = 0;
    while (curr_move < n && t < m && a < l) {
        int mn = min(t_moves[t].second - t_sum, a_moves[a].second - a_sum);
        char t_dir = t_moves[t].first, a_dir = a_moves[a].first;

        int inters = intersections(make_pair(x, y), t_dir, make_pair(x1, y1), a_dir, mn);
        ans += inters;

        if (t_dir == 'U') {
            y -= mn;
        } else if (t_dir == 'D') {
            y += mn;
        } else if (t_dir == 'L') {
            x -= mn;
        } else if (t_dir == 'R') {
            x += mn;
        }

        if (a_dir == 'U') {
            y1 -= mn;
        } else if (a_dir == 'D') {
            y1 += mn;
        } else if (a_dir == 'L') {
            x1 -= mn;
        } else if (a_dir == 'R') {
            x1 += mn;
        }

        t_sum += mn;
        a_sum += mn;
        curr_move += mn;

        if (t_sum == t_moves[t].second) {
            t++;
            t_sum = 0;
        }

        if (a_sum == a_moves[a].second) {
            a++;
            a_sum = 0;
        }
    }

    cout << ans << '\n';
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
