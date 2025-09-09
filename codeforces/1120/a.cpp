#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll

const int MAX_N = 5e5 + 5;

// 1120A: Diana and Liana 
void solve()
{
	int m, k, n, s;
	cin >> m >> k >> n >> s;

	vector<int> vec(m);
	for (int& x: vec)
		cin >> x;

	vector<int> b(s);
	vector<int> cnt(MAX_N+1), used(MAX_N+1), req(MAX_N + 1);
	int unique = 0;
	for (int& x: b) {
		cin >> x;
		req[x]++;
		if (req[x] == 1) unique++;
	}

	set<int> ok;

	auto pick = [&](int x) {
		if (req[x] > 0) {
			cnt[x]++;
			if (cnt[x] >= req[x])
				ok.insert(x);
		}
	};

	auto put = [&](int x) {
		if (req[x] > 0) {
			cnt[x]--;
			if (cnt[x] < req[x])
				ok.erase(x);
		}
	};

	int rest = m - k*n;
	auto check = [&](int l, int r) {
		if (r - l > k + rest) return false;
		return (int) ok.size() == unique;
	};

	int l = 0, r = 0;
	while (r < k + rest) {
		pick(vec[r]);
		r++;
	}

	while (l < m && r < m) {
		if (check(l, r))
			break;

		int l_bound = l + k;
		while (l < l_bound) {
			put(vec[l]);
			l++;
		}

		int r_bound = min(m, l + k + rest);
		while (r < r_bound) {
			pick(vec[r]);
			r++;
		}
	}

	if (check(l, r)) {
#ifndef ONLINE_JUDGE
		cerr << l << ' ' << r << '\n';
		cerr << "DBG: ";
		for (int i = l; i < r; ++i) {
			cerr << vec[i] << ' ';
		}
		cerr << '\n';
#endif // ONLINE_JUDGE

		l = k * (l / k);
		vector<int> ans;
		int sz = 0;
		int to_stay = k - b.size();
		for (int i = l; i < r; ++i) {
			int x = vec[i];
			if (used[x] == req[x]) {
				if (to_stay == 0) {
					ans.push_back(i + 1);
				} else {
					to_stay--;
					sz++;
				}
			} else {
				if (req[x] > 0) used[x]++;
				sz++;
			}

			if (sz == k) {
				break;
			}
		}

		cout << ans.size() << '\n';
		for (int& x: ans)
			cout << x << '\n';
	} else {
		cout << -1 << '\n';
	}
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
