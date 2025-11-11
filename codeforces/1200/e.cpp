#include <iostream>
#include <cassert>
#include <climits>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <map>

using namespace std;
using ll = long long;

#define int ll

const int P = 67;
const int M = 1000006967;
const int maxN = 1e6 + 5;
ll p_pow[maxN];

void precompute()
{
    p_pow[0] = 1;
    for (int i = 1; i < maxN; ++i) {
        p_pow[i] = (p_pow[i-1] * P) % M;
    }
}

// 1200E: Compress Words
void solve()
{
    int n; cin >> n;
    vector<string> vec(n);
    int N = 0;
    for (int i = 0; i < n; ++i) {
        cin >> vec[i];
        N += vec[i].size();
    }

    vector<int> mp(255);
    int d = 1;
    for (char c = '0'; c <= '9'; c++) {
        mp[c] = d++;
    }

    for (char c = 'a'; c <= 'z'; c++) {
        mp[c] = d++;
    }

    for (char c = 'A'; c <= 'Z'; c++) {
        mp[c] = d++;
    }

    int k = 1;
    vector<char> ans(N + 1);
    vector<int> hash(N + 1);
    for (char c: vec.front()) {
        hash[k] = (hash[k-1] + ((mp[c]) * p_pow[k] % M)) % M;
        ans[k] = c;
        k++;
    }

    vector<int> shash(N);

    auto cmp = [&](int l) {
        l = min(l, k);
        int i = k - l;
        int h1 = (M + (hash[k-1] - hash[i-1])) % M;
        int h2 = (shash[l] * p_pow[i-1]) % M;

        return h1 == h2;
    };

    for (int i = 1; i < n; ++i) {
        string& s = vec[i];
        for (int j = 1; j <= (int) s.size(); ++j) {
            shash[j] = (shash[j-1] + ((mp[s[j-1]]) * p_pow[j] % M)) % M;
        }

        int mx = 0;
        for (int j = 1; j <= min(k-1, (int) s.size()); ++j) {
            if (cmp(j)) mx = j;
        }

        for (int j = mx; j < (int) s.size(); ++j) {
            char c = s[j];

            hash[k] = (hash[k-1] + ((mp[c]) * p_pow[k] % M)) % M;
            ans[k] = c;
            k++;
        }
    }

    for (int i = 1; i < k; ++i) {
        cout << ans[i];
    }
    cout << '\n';
}

int T = 1;
int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    precompute();

    // cin >> T;
    while(T--)
        solve();

    return 0;
}
