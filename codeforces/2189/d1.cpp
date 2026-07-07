#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

const int MOD = 1e9 + 7;
const int maxn = 2e5 + 5;
int lp[maxn + 5];

void precompute()
{
    for (int i = 2; i*i <= maxn; ++i) {
        if (lp[i] > 0) continue;

        for (int j = i*i; j <= maxn; j += i) {
            lp[j] = i;
        }
    }
}

int factors(int x)
{
    int cnt = 0;
    if (lp[x] == 0) {
        return 1;
    }

    while (true) {
        if (lp[x] == 0) {
            break;
        }

        cnt++;
        x /= lp[x];
    }

    return cnt;
}


int main()
{
    precompute();
    int mx = 0;
    for (int i = 1; i <= maxn; ++i) {
        mx = max(mx, factors(i));
    }
    cout << mx << '\n';
    return 0;
}
