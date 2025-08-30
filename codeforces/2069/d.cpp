#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAX_N = 2e5;
vector<vector<int>> cnt(MAX_N + 1, vector<int>(26));

const int P1 = 31;
const int P2 = 53;

const int MOD1 = 1e9 + 9;
const int MOD2 = 1e9 + 7;

vector<ll> pref_hash1(MAX_N+1, 0);
vector<ll> pref_hash2(MAX_N+1, 0);

vector<ll> suff_hash1(MAX_N+1, 0);
vector<ll> suff_hash2(MAX_N+1, 0);

vector<ll> pow_p1(MAX_N+1, 0); 
vector<ll> pow_p2(MAX_N+1, 0);

void precompute()
{
	ll current_pow = 1;
	for (int i = 0; i <= MAX_N; ++i) {
		pow_p1[i] = current_pow;
		current_pow = (current_pow * P1) % MOD1;
	}

	current_pow = 1;
	for (int i = 0; i <= MAX_N; ++i) {
		pow_p2[i] = current_pow;
		current_pow = (current_pow * P2) % MOD2;
	}
}

void compute_hashes(string& s)
{
	int n = s.size();
	for (int i = 1; i <= n; ++i) {
		ll term = ((ll)(s[i-1] - 'a' + 1) * pow_p1[i-1]) % MOD1;
		pref_hash1[i] = (pref_hash1[i-1] + term) % MOD1;
	}
	
	for (int i = 1; i <= n; ++i) {
		int index = n-i;
		ll term = ((ll)(s[index] - 'a' + 1) * pow_p1[i-1]) % MOD1;
		suff_hash1[i] = (suff_hash1[i-1] + term) % MOD1;
	}

	for (int i = 1; i <= n; ++i) {
		ll term = ((ll)(s[i-1] - 'a' + 1) * pow_p2[i-1]) % MOD2;
		pref_hash2[i] = (pref_hash2[i-1] + term) % MOD2;
	}
	
	for (int i = 1; i <= n; ++i) {
		int index = n-i;
		ll term = ((ll)(s[index] - 'a' + 1) * pow_p2[i-1]) % MOD2;
		suff_hash2[i] = (suff_hash2[i-1] + term) % MOD2;
	}
}

// [l, r] segment
bool is_palindrome(int l, int r, int n)
{
	int len = (r - l) + 1;
	if (len == 0) return true;

	int l1 = l, r1 = l + (len/2) - 1;

	int l2 = r1 + 1, r2 = r;

	int rev_l2 = n - l2 + 1;
	int rev_r2 = n - r2 + 1;

	ll hash_11 = (MOD1 + ((pref_hash1[r1] - pref_hash1[l1 - 1]) % MOD1)) % MOD1;
	ll hash_12 = (MOD2 + ((pref_hash2[r1] - pref_hash2[l1 - 1]) % MOD2)) % MOD2;

	ll hash_21 = (MOD1 + ((suff_hash1[rev_l2] - suff_hash1[rev_r2 - 1]) % MOD1)) % MOD1;
	ll hash_22 = (MOD2 + ((suff_hash2[rev_l2] - suff_hash2[rev_r2 - 1]) % MOD2)) % MOD2;

	// l2 always greater than l1
	// ll diff = (l2 - rev_l2) - 1;
	// hash_11 = (hash_11 * pow_p1[diff]) % MOD1;
	// hash_12 = (hash_12 * pow_p2[diff]) % MOD2;

	return (hash_11 == hash_21) && (hash_12 == hash_22);
}

bool ok(string& s, int siz)
{
	int n = s.size();
	int half_n = n / 2;
	if (siz <= half_n) {
		// check if last part can be constructed wiht shuffled first part
		int s_l = siz;

		int s_r_l = n - siz;
		int s_r_r = n;

		bool ok = true;
		for (int i = 0; i < 26; ++i) {
			int cnt_l = cnt[s_l][i];
			int cnt_r = cnt[s_r_r][i] - cnt[s_r_l][i];
			ok &= (cnt_l == cnt_r);
		}

		return ok && is_palindrome(s_l + 1, s_r_l, n);
	} else {
		// check if last part can be inside
		int second_l = siz;
		int second_r = n;

		int first_l = 0;
		int first_r = siz;

		// check if palindrome can be constructed by rest of the characters
		vector<int> diff(26);
		for (int i = 0; i < 26; ++i) {
			int cnt_first = cnt[first_r][i] - cnt[first_l][i];
			int cnt_second = cnt[second_r][i] - cnt[second_l][i];
			diff[i] += cnt_first - cnt_second;
		}
		
		bool ok = true;
		for (int i = 0; i < 26; ++i) {
			ok &= (diff[i] >= 0 && diff[i] % 2 == 0);
		}

		return ok;
	}
}

int ans(string& s)
{
	int l = 1, r = s.size();
	int ret = -1;
	while (l <= r) {
		int mid = l + (r - l) / 2;
		if (ok(s, mid)) {
			r = mid - 1;
			ret = mid;
		} else {
			l = mid + 1;
		}
	}

	return ret;
}

void compute_cnt(string& str)
{
	for (int i = 0; i < 26; ++i) {
		cnt[1][i] = 0;
	}

	cnt[1][str[0] - 'a'] = 1;
	for (size_t i = 2ll; i <= str.size(); ++i) {
		for (int j = 0; j < 26; ++j) {
			cnt[i][j] = cnt[i-1][j];
		}

		char c = str[i-1] - 'a';
		cnt[i][c] = cnt[i-1][c] + 1;
	}
}

// 2069D: Palindrome Shuffle
void solve()
{
	string s; cin >> s;
	int n = s.size();
	int l = 0, r = n-1;
	while (l < r && s[l] == s[r])
		l++, r--;

	if (l > r) {
		cout << 0 << '\n';
		return;
	}

	string str;
	for (int i = l; i <= r; ++i)
		str.push_back(s[i]);
	
	compute_cnt(str);
	compute_hashes(str);

	int res = INT_MAX;
	res = min(res, ans(str));

	reverse(str.begin(), str.end());
	compute_cnt(str);

	res = min(res, ans(str));

	cout << res << '\n';
}

int T = 1;
int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

	precompute();

    cin >> T;
    while(T--)
        solve();
    return 0;
}
