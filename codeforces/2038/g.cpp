#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const string A = "1";
const string B = "00";
const string C = "10";

// 2038G: Guess One Character
void solve()
{
	int n; cin >> n;
	int a, b, c;

	cout << "1 " << A << endl;
	cout.flush();
	cin >> a;

	cout << "1 " << B << endl;
	cout.flush();
	cin >> b;

	cout << "1 " << C << endl;
	cout.flush();
	cin >> c;

	// check if string starts with 00
	if (b > 0) {
		// initial 00
		int len = 2;
		len += b-1;
		len += a + c;
		if (len == n) {
			cout << "0 1 0" << endl;
			cout.flush();
			return;
		}
	}

	// check if string starts with 01
	if (a > 0) {
		// initial 01
		int len = 2;
		// intersection of ones and 10s
		len += (a - 1) + c;
		// zeroes at the end
		if (b > 0) {
			if (c > 0) {
				len += b;
			} else {
				len += b + 1;
			}
		}

		if (len == n) {
			cout << "0 1 0" << endl;
			cout.flush();
			return;
		}
	}

	cout << "0 1 1" << endl;
	cout.flush();
}

int T = 1;
int32_t main(void)
{
    cin >> T;
    while(T--) {
		solve();
		int status; cin >> status;
		if (status == -1) break;
	}
    return 0;
}
