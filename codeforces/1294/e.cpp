#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// 1294E: Obtain a Permutation 
void solve()
{
	int n, m;
	cin >> n >> m;
	vector<vector<int>> vec(n, vector<int>(m));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cin >> vec[i][j];
		}
	}

	ll ans = 0;
	for (int j = 0; j < m; ++j) {
		vector<int> head(n+1);
		vector<int> col(n);
		for (int i = 0; i < n; ++i) {
			int x = vec[i][j];
			int id = x - (j + 1);

			if (id % m != 0 || x > n*m) {
				id = -1;
			} else {
				id /= m;
			}

			col[i] = id;
		}

		for (int i = 0; i < n; ++i) {
			int x = col[i];
			if (x != -1) {
				int start = (n + (i - x)) % n;
				head[start]++;
			}
		}

		int mn = INT_MAX;
		for (int i = 0; i < n; ++i) {
			mn = min(mn, n - head[i] + i);
		}

		ans += mn;
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
