#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// 1685B: Linguistics
void solve()
{
	int a, b, c, d;
	cin >> a >> b >> c >> d;

	string s; cin >> s;
	int n = s.size();
	s.insert(0, " ");
	s.push_back(' ');

	int A = 0, B = 0, AB = 0;
	for (int i = 1; i <= n; ++i) {
		char c = s[i];
		if (c == 'A') A++;
		if (c == 'B') B++;
	}

	if (max(0, A - c - d) != a ||
		max(0, B - c - d) != b)
	{
		cout << "NO\n";
		return;
	}

	for (int i = 1; i <= n-1; ++i) {
		char c1 = s[i];
		char c2 = s[i+1];

		if (c1 == 'A' && c2 == 'B') {
			AB++;
		}
	}

	using pii = pair<int, int>;
	using pbb = pair<bool, bool>;
	vector<pii> BA_R;
	pii current = {-1, -1};
	for (int i = 1; i <= n-1; ++i) {
		char c1 = s[i];
		char c2 = s[i+1];
		if (c1 == 'B' && c2 == 'A') {
			if (current.first == -1) {
				current.first = i;
				current.second = i;
			} else {
				current.second = i;
			}
			i++;
		} else {
			if (current.first != -1 && current.second != -1)
				BA_R.push_back(current);
			current = {-1, -1};
		}
	}

	if (current.first != -1 && current.second != -1)
		BA_R.push_back(current);

	vector<pair<pii, pbb>> processed;
	for (int i = 0; i < (int) BA_R.size(); ++i) {
		auto p = BA_R[i];
		pair<pii, pbb> res = { p, {0,0}};
		res.second.first  = s[p.first-1]  == 'A';
		res.second.second = s[p.second+2] == 'B';
		processed.push_back(res);
	}

	sort(processed.begin(), processed.end(), 
	[](pair<pii, pbb>& a, pair<pii, pbb>& b) {
		int len_a = (a.first.second + 1 - a.first.first + 1)/ 2;
		int len_b = (b.first.second + 1 - b.first.first + 1)/ 2;
		int w_a = (a.second.first + a.second.second);
		int w_b = (b.second.first + b.second.second);

		ll l = len_b * (len_a - 1 + w_a);
		ll r = len_a * (len_b - 1 + w_b);

		return l > r;
	});
	
	// use BAs
	int locked_AB = 0;
	int used_BA = 0;
	while (used_BA < d && processed.size() > 0) {
		int diff = d - used_BA;
		auto p = processed.back();
		int l = p.first.first;
		int r = p.first.second + 1;
		int BA_cnt = (r - l + 1) / 2;
		if (BA_cnt <= diff) {
			int AB_cnt = BA_cnt - 1 + (int) p.second.first + (int) p.second.second;
			used_BA += BA_cnt;
			locked_AB += AB_cnt;
			processed.pop_back();
		} else {
			BA_cnt = diff;
			int AB_cnt = 0;
			if (p.second.first) {
				AB_cnt = BA_cnt - 1 + (int) p.second.second + 1;
			} else {
				AB_cnt = BA_cnt - 1 + (int) p.second.first + 1;
			}

			used_BA += BA_cnt;
			locked_AB += AB_cnt;

			break;
		}
	}

	bool ok = false;
	//cerr << used_BA << ' ' << locked_AB << '\n';
	if (used_BA == d) {
		AB -= locked_AB;
		assert(AB >= 0);
		if (AB >= c) {
			ok = true;
		}
	}

#if 0
	// stress test
	vector<string> perm;
	for (int i = 0; i < a; ++i)
		perm.push_back("A");
	for (int i = 0; i < b; ++i)
		perm.push_back("B");
	for (int i = 0; i < c; ++i)
		perm.push_back("AB");
	for (int i = 0; i < d; ++i)
		perm.push_back("BA");
	bool actually_ok = false;
	sort(perm.begin(), perm.end());
	do {
		int pt = 1;
		bool loc_ok = true;
		for (string& str: perm) {
			if (str[0] != s[pt++]) {
				loc_ok = false;
			}
			if (str.size() == 2) {
				if (str[1] != s[pt++])
					loc_ok = false;
			}
		}

		actually_ok |= loc_ok;
	} while (!actually_ok && next_permutation(perm.begin(), perm.end()));


	//cerr << boolalpha;
	//cerr << actually_ok << ' ' << ok << '\n';
	assert(actually_ok == ok);
#endif

	cout << (ok ? "YES\n" : "NO\n");
}

void gen(char** argv)
{
	static int RANGE = 9;

	int seed = stoi(argv[1]);
	srand(seed);
	int a = rand() % (RANGE + 1);
	RANGE -= a;
	int b = rand() % (RANGE + 1);
	RANGE -= b;
	int c = rand() % (RANGE + 1);
	RANGE -= c;
	int d = rand() % (RANGE + 1);

	vector<string> perm;
	for (int i = 0; i < a; ++i)
		perm.push_back("A");
	for (int i = 0; i < b; ++i)
		perm.push_back("B");
	for (int i = 0; i < c; ++i)
		perm.push_back("AB");
	for (int i = 0; i < d; ++i)
		perm.push_back("BA");

	mt19937 gen(seed);

	for (int i = perm.size() - 1; i > 0; --i) {
		uniform_int_distribution<int> dist(0, i);
		int j = dist(gen);
		swap(perm[i], perm[j]);
	}

	cout << 1 << '\n';
	cout << a << ' ' << b << ' ' << c << ' ' << d << '\n';
	for (string& s: perm)
		cout << s;
	cout << '\n';
}

int T = 1;
int32_t main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

	if (argc == 2) {
		gen(argv);
		return 0;
	}

    cin >> T;
    while(T--)
        solve();
    return 0;
}
