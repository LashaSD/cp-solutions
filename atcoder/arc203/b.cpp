#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// ARC203B: Swap If Equal Sum 
void solve()
{
	int n; cin >> n;
	vector<int> veca(n), vecb(n);

	for (int& x: veca) cin >> x;
	for (int& x: vecb) cin >> x;

	int a_ones = 0, b_ones = 0;
	for (int i = 0; i < n; ++i) {
		a_ones += veca[i];
		b_ones += vecb[i];
	}

	bool eq = true;
	for (int i = 0; i < n; ++i) {
		if (veca[i] != vecb[i]) {
			eq = false;
			break;
		}
	}

	if (eq) {
		cout << "Yes\n";
		return;
	} else if (a_ones != b_ones) {
		cout << "No\n";
		return;
	}

	if ((a_ones == 0) ||
		(a_ones == 1 && 
		(veca.front() || veca.back() || vecb.front() || vecb.back()))) 
	{
		cout << "No\n";
	} else {
		cout << "Yes\n";
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
