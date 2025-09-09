#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll

// 1054D: Changing Array 
void solve()
{
	int n, k;
	cin >> n >> k;
	vector<int> vec(n);
	for (int& x: vec)
		cin >> x;

	int high = (1ll << k) - 1;
	for (int i = 0; i < n; ++i) {
		vec[i] = min(vec[i], high - vec[i]);
	}

	vector<int> pref(n+1);
	for (int i = 0; i < n; ++i) {
		pref[i+1] = pref[i] ^ vec[i];
	}

	map<int, int> oc;
	for (int i = 0; i <= n; ++i) {
		oc[pref[i]]++;
	}

	ll ans = 0;
	for (auto [x, f]: oc) {
		int comp_pairs = (f/2);
		int norm_pairs = (f+1)/2;

		comp_pairs = comp_pairs*(comp_pairs-1) / 2;
		norm_pairs = norm_pairs*(norm_pairs-1) / 2;

		ans += comp_pairs + norm_pairs;
	}

	cout << n*(n+1) / 2 - ans << '\n';
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
