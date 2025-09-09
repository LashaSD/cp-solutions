#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// 1428D: Bouncing Boomerangs 
void solve()
{
	int n; cin >> n;
	vector<int> vec(n);
	for (int& x: vec)
		cin >> x;

	vector<pair<int, int>> ans(n, {-1, -1});
	set<int> ones, twos, threes;
	int row = 1;
	for (int i = 0; i < n; ++i) {
		if (vec[i] == 1) {
			ones.insert(i+1);
		} else if (vec[i] == 2) {
			twos.insert(i+1);
		} else if (vec[i] == 3) {
			threes.insert(i+1);
		}
	}

	for (int i = 0; i < n; ++i) {
		int x = vec[i];
		if (ans[i].first > 0) continue;
		if (x == 0) continue;

		if (x == 1) {
			ans[i].first = row;
			row++;
		} else if (x == 2) {
			auto one_it = ones.upper_bound(i+1);
			if (one_it == ones.end()) {
				cout << -1 << '\n'; return;
			}

			ans[i].first = row;
			ans[*one_it - 1].first = row;
			row++;
			ones.erase(one_it);
		} else if (x == 3) {
			auto three_it = threes.upper_bound(i+1);
			if (three_it != threes.end()) {
				ans[i].first = row;
				ans[*three_it - 1].second = row;
				threes.erase(three_it);
				row++;
				continue;
			}

			auto two_it = twos.upper_bound(i+1);
			if (two_it != twos.end()) {
				ans[i].first = row;
				ans[*two_it - 1].second = row;
				twos.erase(two_it);
				row++;
				continue;
			}

			auto one_it = ones.upper_bound(i+1);
			if (one_it == ones.end()) {
				cout << -1 << '\n'; return;
			}

			ans[i].first = row;
			ans[*one_it - 1].first = row;
			ans[*one_it - 1].second = row+1;
			row += 2;
			ones.erase(one_it);
		}
	}

	vector<pair<int, int>> out;
	for (int i = 0; i < n; ++i) {
		auto p = ans[i];
		if (p.first != -1) {
			out.push_back({p.first, i+1});
		}
		if (p.second != -1) {
			out.push_back({p.second, i+1});
		}
	}

	cout << out.size() << '\n';
	for (auto p: out) {
		cout << p.first << ' ' << p.second << '\n';
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
