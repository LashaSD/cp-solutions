#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// 1912A: Accumulator Apex
void solve()
{
	ll x, n;
	cin >> x >> n;
	vector<vector<ll>> vec(n);
	for (int i = 0; i < n; ++i) {
		int m; cin >> m;
		vec[i].resize(m);
		for (int j = 0; j < m; ++j) {
			cin >> vec[i][j];
		}
	}

	// X: 1 COST: 0 GAIN: 1
	// X: 2 COST: 2 GAIN: 4
	// X: 4 COST: 3 GAIN: 0
	// X: 4 COST: 4 GAIN: 8

	// { cost, gain }, profit = gain - cost
	vector<vector<pair<ll, ll>>> blocks(n);
	for (int i = 0; i < n; ++i) {
		pair<ll, ll> block;
		bool in_profit = false;
		ll cost_accum = 0;
		for (size_t j = 0; j < vec[i].size(); ++j) {
			ll y = vec[i][j];
			if (in_profit && y < 0) {
				blocks[i].push_back(block);
				block = {0, 0};
				in_profit = false;
				cost_accum = 0;
			}

			if (y < 0) {
				cost_accum += -y;
				block.second = max(0ll, block.second + y);
			} else if (y > 0) {
				block.first = max(block.first, cost_accum);
				cost_accum -= y;

				block.second += y;
				if (block.second >= block.first) {
					in_profit = true;
				}
			}
		}

		if (in_profit) {
			blocks[i].push_back(block);
		}
	}

	multiset<pair<ll, pair<ll, ll>>> st;
	for (int i = 0; i < n; ++i) {
		if (blocks[i].size() == 0) continue;

		reverse(blocks[i].begin(), blocks[i].end());
		auto p = blocks[i].back();
		st.insert({p.first, {p.second, i}});
		blocks[i].pop_back();
	}

	while (!st.empty()) {
		auto it = st.begin();
		ll cost = it->first;
		ll gain = it->second.first;
		ll profit = gain - cost;
		ll index = it->second.second;

#ifndef ONLINE_JUDGE
		cerr << "X: " << x << " COST: " << cost << " GAIN: " << gain << '\n';
#endif // ONLINE_JUDGE

		if (x < cost) break;

		if (profit > 0) {
			x += profit;
		}

		st.erase(it);
		if (blocks[index].size() > 0) {
			auto p = blocks[index].back();
			st.insert({p.first, {p.second, index}});
			blocks[index].pop_back();
		}
	}

	cout << x << '\n';
}

int T = 1;
int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // cin >> T;
    while(T--)
        solve();
    return 0;
}
