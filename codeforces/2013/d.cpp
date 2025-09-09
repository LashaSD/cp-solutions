#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// 2013D: Minimize the Difference
void solve()
{
	int n; cin >> n;
	vector<ll> vec(n);
	for (ll& x: vec)
		cin >> x;

	vector<ll> pref(n+1);
	pref[1] = vec[0];
	ll sum = vec[0];
	for (int i = 1; i < n; ++i) {
		sum += vec[i];
		int cnt = i + 1;
		pref[i+1] = min(pref[i], sum / cnt);
	}

	vector<ll> suff(n+1);
	suff[n-1] = vec.back();
	sum = vec[n-1];
	for (int i = n-2; i >= 0; --i) {
		sum += vec[i];
		int cnt = n - i;
		suff[i] = max(suff[i+1], (sum + cnt - 1) / cnt);
	}

	//cerr << "DBG: " << suff[0] << ' ' << pref[n] << '\n';
	cout << suff[0] - pref[n] << '\n';
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
