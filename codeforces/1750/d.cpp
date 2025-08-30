#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAX_X = 1e9;
const int MOD = 998244353;

vector<int> primes;
vector<int> primes_first;
void precompute()
{
	for (int i = 2; i*i <= MAX_X; ++i) {
		// check if i is prime
		bool is_prime = true;
		for (int j = 2; j*j <= i; ++j) {
			if (i % j == 0) {
				is_prime = false;
				break;
			}
		}

		if (is_prime) {
			primes.push_back(i);
		}
	}
}

vector<int> distinct_primes(vector<int>& primes, int n)
{
	vector<int> loc_primes;
	int num = n;

	for (int i = 0; i < primes.size(); ++i) {
		int p = primes[i];

		if (num % p == 0) loc_primes.push_back(p);

		while (num % p == 0) {
			num /= p;
		}

		if (num <= 1) break;
	}

	if (num > 1) loc_primes.push_back(num);

	return loc_primes;
}

// 1750D: Count GCD
void solve()
{
	int n, m;
	cin >> n >> m;
	vector<int> vec(n);

	for (int& x: vec)
		cin >> x;

	for (int i = 1; i < n; ++i) {
		if (vec[i-1] % vec[i] != 0) {
			cout << 0 << '\n';
			return;
		}
	}

	primes_first = move(distinct_primes(primes, vec[0]));

	vector<int> ans(n);
	ans[0] = 1;
	for (int i = 1; i < n; ++i) {
		int a = vec[i-1] / vec[i];
		int limit = m / vec[i];

		vector<int> loc_primes = distinct_primes(primes_first, a);
		ll cnt = 0;
		int max_mask = (1 << loc_primes.size()) - 1;
		for (int mask = 1; mask <= max_mask; ++mask) {
			int p = 1;
			for (int j = 0; j < loc_primes.size(); ++j) {
				int bit = (1 << j);
				if ((mask & bit) != 0) {
					p *= loc_primes[j];
				}
			}

			bool is_odd = __builtin_popcount(mask) % 2;
			if (is_odd)
				cnt += limit / p;
			else
				cnt -= limit / p;
		}

		ans[i] = limit - cnt;
	}

	ll ret = ans[0];
	for (int i = 1; i < n; ++i) {
		ret = (ret * (ans[i] % MOD)) % MOD;
	}

	cout << ret << '\n';
}

int T = 1;
int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

	precompute();
	//test();
	//return 0;

    cin >> T;
    while(T--)
        solve();
    return 0;
}
