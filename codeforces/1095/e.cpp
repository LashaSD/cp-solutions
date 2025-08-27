#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// 1095E: Almost Regular Bracket Sequence
void solve()
{
	int n; cin >> n;
	string s; cin >> s;
	vector<int> pref(n+1);
	for (int i = 0; i < n; ++i) {
		char c = s[i];
		pref[i+1] = pref[i] + (c == '(' ? 1 : -1);
	}

	vector<int> suff_min(n+1), pref_min(n+1);
	suff_min[n] = pref[n];
	for (int i = n-1; i >= 0; --i) {
		suff_min[i] = min(suff_min[i+1], pref[i]);
	}

	pref_min[1] = pref[1];
	for (int i = 2; i <= n; ++i) {
		pref_min[i] = min(pref_min[i-1], pref[i]);
	}

	int cnt = 0;
	for (int i = 0; i < n; ++i) {
		char c = s[i];
		int base = (c == '(' ? 2 : -2);
		if (suff_min[i+1] >= base && pref[n] == base && pref_min[i] >= 0) {
			cnt++;
		}
	}

	cout << cnt << '\n';
}

int T = 1;
int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(T--)
        solve();
    return 0;
}
