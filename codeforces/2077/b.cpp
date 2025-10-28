#include <iostream>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <bitset>
#include <map>

using namespace std;
using ll = long long;

#define int ll

// 2077B: Finding OR Sum
void solve()
{
    int a1 = 0, a2 = 0;
    for (int i = 0; i < 30; i += 2) {
        a1 |= (1ll << i);
    }

    for (int i = 1; i < 30; i += 2) {
        a2 |= (1ll << i);
    }

    int s1, s2;

    cout << a1 << '\n';
    cout.flush();
    cin >> s1;

    cout << a2 << '\n';
    cout.flush();
    cin >> s2;

    int x = 0, y = 0;

    // special case for ...0001
    {
        int bit = 1;
        if ((bit & s1) == bit) {
            x |= bit;
        } else if (((bit << 1ll) & s1) != 0) {
            x |= bit;
            y |= bit;
        }
    }

    for (int i = 2; i < 30; i += 2) {
        int bit = (1ll << i);

        if ((bit & s2) == 0 && ((bit << 1ll) & s2) != 0) {
            x |= bit;
        } else if ((bit & s2) != 0 && ((bit << 1ll) & s2) != 0) {
            x |= bit;
            y |= bit;
        }
    }

    for (int i = 1; i < 30; i += 2) {
        int bit = (1ll << i);

        if ((bit & s1) == 0 && ((bit << 1ll) & s1) != 0) {
            x |= bit;
        } else if ((bit & s1) != 0 && ((bit << 1ll) & s1) != 0) {
            x |= bit;
            y |= bit;
        }
    }

    cout << "!\n";
    cout.flush();

    int m;
    cin >> m;

    cout << (x | m) + (y | m) << '\n';
    cout.flush();
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
