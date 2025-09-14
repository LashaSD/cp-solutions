#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int n, m;

ll mx_row(vector<vector<ll>>& vec)
{
	ll mx_sum = 0;
	ll index = -1;
	for (int i = 0; i < n; ++i) {
		ll sum = 0;
		for (int j = 0; j < m; ++j) {
			sum += vec[i][j];
		}

		if (sum > mx_sum) {
			index = i;
			mx_sum = sum;
		}
	}

	if (index != -1) {
		for (int j = 0; j < m; ++j) {
			vec[index][j] = 0;
		}
	}
	
	//cerr << "ROW: " << index << '\n';
	return mx_sum;
}

ll mx_col(vector<vector<ll>>& vec)
{
	ll mx_sum = 0;
	ll index = -1;
	for (int j = 0; j < m; ++j) {
		ll sum = 0;
		for (int i = 0; i < n; ++i) {
			sum += vec[i][j];
		}

		if (sum > mx_sum) {
			index = j;
			mx_sum = sum;
		}
	}

	if (index != -1) {
		for (int i = 0; i < n; ++i) {
			vec[i][index] = 0;
		}
	}
	
	return mx_sum;
}

// 1219G: Harvester
void solve()
{
	cin >> n >> m;
	vector<vector<ll>> vec(n, vector<ll>(m));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cin >> vec[i][j];
		}
	}

	ll ans = 0;
	int max_mask = (1 << 4) - 1;
	for (int mask = 0; mask <= max_mask; ++mask) {
		vector<vector<ll>> cp = vec;
		ll loc_sum = 0;
		for (int i = 0; i < 4; ++i) {
			int bit = (1 << i);
			if ((bit & mask) != 0) {
				loc_sum += mx_row(cp);
			} else {
				loc_sum += mx_col(cp);
			}
		}	
		ans = max(ans, loc_sum);
	}

	cout << ans << '\n';
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
