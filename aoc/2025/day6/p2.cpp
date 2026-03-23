#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

bool only_space(const string& s)
{
    for (char c: s) {
        if (c != ' ') return false;
    }

    return true;
}

void parse(const string& s, vector<string>& out)
{
    out.clear();
    for (auto it = s.begin(); it != s.end(); ) {
        auto del = find(it, s.end(), ' ');
        string tmp = string(it, del);
        if (!only_space(tmp)) {
            out.emplace_back(move(tmp));
        }

        if (del == s.end()) break;
        it = del + 1;
    }
}

ll reversell(ll x)
{
    ll num = 0;
    ll tmp = x, k = 0;
    while (tmp > 0) {
        tmp /= 10;
        k++;
    }

    while (x > 0) {
        num += powl(10ll, k-1) * (x % 10);
        x /= 10;
        k--;
    }

    return num;
}

void read(vector<vector<int>>& nums, vector<char>& ops)
{
    string buf;
    vector<string> parsed;
    int n;
    while (getline(cin, buf)) {
        parse(buf, parsed);
        n = parsed.size();
        nums.resize(n);
        ops.resize(n);
        for (int i = 0; i < n; ++i) {
            if (!isdigit(parsed[i].front())) {
                ops[i] = parsed[i].front();
            } else {
                ll x = stoll(parsed[i]);
                nums[i].push_back(reversell(x));
            }
        }
    }
}

// AOC2025: Trash Compactor
// day 6 part 1
signed main()
{
    vector<vector<int>> nums;
    vector<char> ops;
    read(nums, ops);

    ll ans = 0;
    for (int i = 0; i < (int) nums.size(); ++i) {
        const vector<int>& col = nums[i];
        char o = ops[i];
        ll sum = 0, prod = 1;
        for (int x: col) {
            prod *= x;
            sum += x;
        }

        if (o == '*')
            ans += prod;
        else
            ans += sum;
    }

    cout << ans << '\n';
}
