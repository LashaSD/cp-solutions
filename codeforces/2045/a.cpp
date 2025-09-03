#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll

// 2045A: Scrambled Scrabble 
void solve()
{
	string s;
	cin >> s;
	int vowels = 0;
	int consonants = 0;
	int N = 0;
	int G = 0;
	int Y = 0;
	for (char c: s) {
		if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') 
			vowels++;
		else if (c == 'Y')
			Y++;
		else {
			consonants++;
			if (c == 'N')
				N++;
			else if (c == 'G')
				G++;
		}
	}

	int used_consonants = 0;

	// CVC
	int CVC = min(vowels, consonants / 2);
	vowels -= CVC;
	consonants -= 2 * CVC;
	used_consonants += 2 * CVC;

	// CYC
	int CYC = min(Y, consonants / 2);
	Y -= CYC;
	consonants -= 2 * CYC;
	used_consonants += 2 * CYC;


	// YVY and CVY and YVC
	int YVY = min(vowels, (consonants + Y) / 2);
	vowels -= YVY;
	int used = 2 * YVY;
	consonants -= max(0ll, used - Y);
	Y = max(0ll, Y - used);

	used_consonants += 2 * YVY;

	// YYY
	int YYY = Y / 3;
	Y -= 3*YYY;
	used_consonants += 2 * YYY;

	consonants += Y;

	// use as many N s as consonants as possible
	// make sure if consonants need to be leftover as many G s are leftover as possible
	// the amount of N being used is min(used_consonants, N);
	// the amount of G leftover is min(consonants, G)
	// pair up used N with leftover G
	int replacements = min({used_consonants, N, consonants, G});

	//cerr << "DBG: " << used_consonants << ' ' << '\n';
	ll ans = 3 * (CVC + CYC + YVY + YYY) + replacements;
	cout << ans << '\n';
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
