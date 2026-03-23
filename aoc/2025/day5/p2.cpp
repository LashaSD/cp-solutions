#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

void read(vector<pair<ll, ll>>& ranges)
{
    string buf;
    while (cin >> buf) {
        auto split = find(buf.begin(), buf.end(), '-');
        if (split == buf.end()) return;
        ll l = stoll(string(buf.begin(), split));
        ll r = stoll(string(split + 1, buf.end()));
        ranges.push_back(make_pair(l, r));
    }
}

ll unionLen(const vector<pair<ll, ll>>& ranges)
{
    vector<pair<ll, bool>> ends;
    for (auto [l, r]: ranges) {
        ends.push_back(make_pair(l - 1, 1));
        ends.push_back(make_pair(r, 0));
    }

    sort(ends.begin(), ends.end());

    int c = 0;
    ll ans = 0;
    for (int i = 0; i < (int) ends.size(); ++i) {
        if (c > 0 && i > 0) {
            ans += ends[i].xx - ends[i-1].xx;
        }

        if (ends[i].yy) c++;
        else c--;
    }

    return ans;
}

// AOC2025: Cafeteria
// day 5 part 2
signed main()
{
    vector<pair<ll, ll>> ranges;
    read(ranges);
    cout << unionLen(ranges) << '\n';
}
