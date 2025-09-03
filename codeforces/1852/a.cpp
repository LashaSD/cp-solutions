#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int INF = 2e9;

#define int ll

// 1852A: Ntarsis' Set
void solve()
{
	int n, k;
	cin >> n >> k;
	
	vector<int> vec(n);
	for (int i = 0; i < n; ++i) {
		cin >> vec[i];
	}

	ll pivot = 1;
	for (int i = 0; i < n; ++i) {
		if (vec[i] == pivot) {
			pivot++;
		}
	}

	for (int i = 0; i < (k - 1); ++i) {
		// get the hop size 
		auto border = upper_bound(vec.begin(), vec.end(), pivot);
		int hop_size = border - vec.begin();

		int dist_to_border = INF;
		if (border != vec.end()) {
			dist_to_border = *border - pivot;
		}

		if (dist_to_border > hop_size) {
			pivot += hop_size;
			continue;
		}

		int borders = 1;
		auto l_border = border;
		auto r_border = border + 1;
		while (r_border != vec.end()) {
			int r = *r_border;
			int landing = pivot + hop_size + borders;
			if (landing < r) {
				pivot = landing;
				break;
			} else {
				borders++;
				l_border++;
				r_border++;
			}
		}

		if (r_border == vec.end()) {
			pivot += hop_size + borders;
		}
	}

	cout << pivot << '\n';
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
