#include <bits/stdc++.h>
#include <stdio.h>

using namespace std;
using ll = long long;

// 2039C2: Shohag Loves XOR (Hard Version)
void solve()
{
	ll x, m;
	cin >> x >> m;

	ll y_cnt = 0;
	ll x_cnt = 0;
	for (ll y = 1; y <= min(x, m); ++y) {
		ll z = y ^ x;
		// only divisible by y not x 
		if (z % y == 0 && z % x != 0) {
			// cerr << "Y: " << y << '\n';
			y_cnt++;
		} else if (z % x == 0) {
			// divisible by x and possibly y
			x_cnt++;
		}
	}

	if (x >= m) {
		cout << y_cnt + x_cnt << '\n';
		return;
	}

	const ll BIT_CNT = 63;

	ll sum = 1;
	ll pref = 0;
	for (ll i = BIT_CNT; i >= 0; --i) {
		ll bit = (1ll << i);
		ll m_bit = m & bit;
		ll x_bit = x & bit;

		ll loc_pref = pref;
		loc_pref |= (m_bit ^ x_bit) ^ bit;

		if (m_bit != 0 && i > 0) {
			// count how many different combinations of bits make up a multiple of x
			ll upper = loc_pref | (bit - 1ll);
			ll upper_cnt = 0;
			if (upper > 0) upper_cnt = upper / x;

			ll lower = max(0ll, loc_pref - 1);
			ll lower_cnt = 0;
			if (lower > 0) lower_cnt = lower / x;

			ll cnt = upper_cnt - lower_cnt;

			// only way we can get get x ^ y = x, is if y = 0, 
			// and y can't be 0 by problem constraints
			if (lower < x && x <= upper) cnt--;

			//cerr << "LPREF: " << bitset<8>(loc_pref) << '\n';
			//cerr << "UPPER: " << bitset<8>(upper)    << '\n';
			//cerr << "LOWER: " << bitset<8>(lower)    << '\n';
			//cerr << "CNT: "   << cnt                 << '\n';

			//cerr << "DBG: " << upper << ' ' << lower << ' ' << cnt << '\n';

			sum += cnt;
		} else if (i == 0) {
			if (m_bit != 0) { 
				ll xored = pref;
				sum += (ll)(xored % x == 0 && xored != x && xored != 0);

				xored = (pref | bit);
				sum += (ll)(xored % x == 0 && xored != x && xored != 0);
			} else if (x_bit != 0) {
				ll xored = (pref | bit);
				sum += (ll)(xored % x == 0 && xored != x && xored != 0);
			} else {
				ll xored = pref;
				sum += (ll)(xored % x == 0 && xored != x && xored != 0);
			}
		}

		pref |= (m_bit ^ x_bit);
	}

	// cerr << "BIT: " << bitset<8>(pref) << '\n';

	//cerr << "Y: " << y_cnt << '\n';
	// cout << "ANS: ";
	cout << y_cnt + sum << '\n';
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
