#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

void read(vector<pair<ll, ll>>& ranges, vector<ll>& queries)
{
    string buf;
    while (cin >> buf) {
        auto split = find(buf.begin(), buf.end(), '-');
        if (split != buf.end()) {
            ll l = stoll(string(buf.begin(), split));
            ll r = stoll(string(split + 1, buf.end()));
            ranges.push_back(make_pair(l, r));
        } else {
            queries.push_back(stoll(buf));
        }
    }
}

// AOC2025: Cafeteria
// day 5 part 1
signed main()
{
    vector<pair<ll, ll>> ranges;
    vector<ll> queries;
    read(ranges, queries);
    sort(ranges.begin(), ranges.end());
    sort(queries.begin(), queries.end());

    int qi = 0, ri = 0;
    int qn = queries.size(), rn = ranges.size();
    int ans = 0;
    while (qi < qn && ri < rn) {
        auto [l, r] = ranges[ri];
        ll x = queries[qi];
        while (x < l) {
            qi++;
            if (qi == qn) break;
            x = queries[qi];
        }

        if (x > r) {
            ri++;
        } else {
            ans++;
            qi++;
        }
    }

    cout << ans << '\n';
}
