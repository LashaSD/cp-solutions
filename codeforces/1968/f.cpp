#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// 1968F: Equal XOR Segments
void solve()
{
	int n, q;
	cin >> n >> q;
	vector<int> vec(n);
	for (int& x: vec)
		cin >> x;

	vector<int> pref(n+1);
	pref[0] = 0;
	for (int i = 1; i <= n; ++i) {
		pref[i] = pref[i-1] ^ vec[i-1];
	}

	map<int, vector<int>> mp;
	for (int i = 0; i < n; ++i) {
		int x = pref[i+1];
		mp[x].push_back(i+1);
	}

	auto ok_pref = [&](int l, int r) {
		int xored = pref[r] ^ pref[l-1];
		if (xored == 0) return true;

		vector<int>& f = mp[xored ^ pref[l-1]];

		auto found = lower_bound(f.begin(), f.end(), l);
		if (found == f.end() || *found >= r) return false;

		int k = pref[*found] ^ xored;
		vector<int>& g = mp[k];
		if (g.empty()) return false;

		found = upper_bound(g.begin(), g.end(), *found);
		if (found == g.end() || *found >= r) return false;

		return true;
	};

	for (int i = 0; i < q; ++i) {
		int l, r;
		cin >> l >> r;
		if (ok_pref(l, r)) {
			cout << "YES\n";
		} else {
			cout << "NO\n";
		}
	}
}

int T = 1;
int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while(T--) {
        solve();
		cout << '\n';
	}
    return 0;
}
