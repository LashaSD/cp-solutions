#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

vector<ll> powers;
const int MAX_POW = 20;

void precompute()
{
    ll i = 1;
    int pow = 0;
    while (pow <= MAX_POW) {
        powers.push_back(i);
        i *= 3;
        pow++;
    }
}

// 2132C2: The Cunning Seller (hard version)
void solve()
{
    int n, k;
    cin >> n >> k;
    vector<ll> vec;
    for (int num = n, i = MAX_POW; i >= 0; i--) {
        ll x = powers[i];
        int digit = 0;
        while (num >= x) {
            num -= x;
            digit++;
        }

        vec.push_back(digit);
    }

    ll sum = 0;
    for (int i = 0; i <= MAX_POW; ++i) sum += vec[i];

    if (sum > k) {
        cout << -1 << '\n';
        return;
    }

    auto f = [&](ll x) {
        return powers[x+1] + x * powers[x-1];
    };

    for (int j = 0; j < MAX_POW; ++j) {
        ll dgt = vec[j];

        ll l = 0, r = dgt;
        ll cnt = max(0ll, (k - sum) / 2);
        cnt = min(cnt, dgt);

        vec[j+1] += 3*cnt;
        vec[j] -= cnt;

        sum += 2*cnt;
    }

    dbg(vec);
    ll coins = 0;
    for (int j = MAX_POW, p = 0; j >= 0; --j, p++) {
        ll dgt = vec[j];
        coins += dgt * f(p);
    }

    cout << coins << '\n';
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
