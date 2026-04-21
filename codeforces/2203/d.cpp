#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2203D: Divisibility Game
void solve()
{
    int n, m;
    cin >> n >> m;
    int N = n + m;
    vector<int> veca(n), vecb(m);
    for (int i = 0; i < n; ++i) {
        cin >> veca[i];
    }

    for (int i = 0; i < m; ++i) {
        cin >> vecb[i];
    }

    sort(veca.begin(), veca.end());
    // unique vec of a
    vector<int> uvec;
    uvec.reserve(n);
    uvec.push_back(veca.front());
    for (int i = 1; i < n; ++i) {
        if (veca[i] != uvec.back()) {
            uvec.push_back(veca[i]);
        }
    }

    // freaky[y] = how many x's are divisible by y
    vector<int> freaky(N+1);
    for (int x: uvec) {
        //cerr << x << ' ';
        for (int y = x; y <= N; y += x) {
            freaky[y]++;
        }
    }
    //cerr << '\n';

    // a - only alice
    // b - only bob
    // c - both
    int a = 0, b = 0, c = 0;
    for (int y: vecb) {
        if (freaky[y] == 0) {
            b++;
        } else if (freaky[y] == (int) uvec.size()) {
            a++;
        } else {
            c++;
        }
    }

    // cerr << a << ' ' << b << ' ' << c << '\n';
    bool bob = 0;
    if (c % 2 == 1 && b > a) {
        bob = 1;
    } else if (c % 2 == 0 && b >= a) {
        bob = 1;
    }

    if (bob)
        cout << "Bob\n";
    else
        cout << "Alice\n";
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
