#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll

// 2021C2: Adjust The Presentation (Hard Version)
void solve()
{
	int n, m, q;
	cin >> n >> m >> q;

	vector<int> a(n), b(m);
	for (int& x: a)
		cin >> x;

	for (int& x: b)
		cin >> x;

	vector<int> order(n+1, 0), pos(n+2, m);
	vector<set<int>> oc(n+1);
	set<pair<int, int>> ruined;

	pos[0] = 0;
	pos[n+1] = m+1;

	for (int i = 0; i < n; ++i) {
		int x = a[i];
		order[x] = i+1;
	}

	for (int i = 0; i < m; ++i) {
		int x = b[i];
		pos[order[x]] = min(i, pos[order[x]]);
		oc[x].insert(i);
	}

	auto check_order = [&pos, &ruined](int ord) {
		if (pos[ord-1] <= pos[ord]) {
			ruined.erase({ord-1, ord});
		} else {
			ruined.insert({ord-1, ord});
		}

		if (pos[ord] <= pos[ord+1]) {
			ruined.erase({ord, ord+1});
		} else {
			ruined.insert({ord, ord+1});
		}
	};

	for (int i = 1; i <= n; ++i) {
		check_order(i);
	}

	cout << (ruined.size() == 0 ? "YA\n" : "TIDAK\n");

	for (int i = 0; i < q; ++i) {
		int j, y;
		cin >> j >> y;
		j--;

		int x = b[j];
		b[j] = y;

		int ord = order[x];
		set<int>& pos_x = oc[x];

		pos_x.erase(j);
		pos[ord] = (pos_x.empty() ? m : *pos_x.begin());

		set<int>& pos_y = oc[y];
		pos_y.insert(j);
		int ord_y = order[y];

		pos[ord_y] = *pos_y.begin();

		check_order(ord);
		check_order(ord_y);

		cout << (ruined.size() == 0 ? "YA\n" : "TIDAK\n");
	}
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
