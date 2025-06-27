#include <algorithm>
#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
// #include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

const int maxN = (int) 1e5 + 5;

vector<int> divs[maxN];

void precompute()
{
    for (int i = 1; i < maxN; ++i) {
        for (int j = i; j < maxN; j += i) {
            divs[j].push_back(i);
        }
    }
}

// C. Quiz Master
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> vec(n), cnt(maxN, 0);
    vector<bool> processed(maxN, 0);
    for (int i = 0; i < n; ++i) {
        cin >> vec[i];
    }

    sort(vec.begin(), vec.end());

    int T = 0;
    int ans = -1;
    for (int l = 0, r = 0; l < n; ++l) {
        // reset previous l
        if (l > 0 && processed[vec[l-1]]) {
            int num = vec[l-1];
            for (int div : divs[num]) {
                if (div <= m) {
                    cnt[div]--;
                    if (cnt[div] == 0) {
                        T--;
                    }
                }
            }
            processed[num] = false;
        }

        r = max(l, r);
        for (; r < n; ++r) {
            int num = vec[r];
            if (!processed[num]) {
                for (int div : divs[num]) {
                    if (div <= m) {
                        cnt[div]++;
                        if (cnt[div] == 1) {
                            T++;
                        }
                    }
                }
                processed[num] = true;
            }

            if (T == m) {
                if (ans == -1) {
                    ans = vec[r] - vec[l];
                } else {
                    ans = min(ans, vec[r] - vec[l]);
                }
                break;
            }
        }
    }

    cout << ans << '\n';
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

