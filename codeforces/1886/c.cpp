#include <bits/stdc++.h>
#include <queue>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

// 1886C: Decreasing String
void solve()
{
    string s; cin >> s;
    int n = s.size();
    ll pos; cin >> pos;

    int s_i = 0;
    ll pos_it = 0;
    int real_index = -1;
    for (int i = n; i >= 1; pos_it += i, i--, s_i++) {
        if ((pos_it + i) >= pos) {
            real_index = (pos - pos_it) - 1;
            break;
        }
    }

    // inversion is an index i, such that s[i] > s[i+1]
    set<int> inversions;
    set<int> undeleted;
    for (int i = 0; i < n-1; ++i) {
        if (s[i] > s[i+1]) inversions.insert(i);
        undeleted.insert(i);
    }
    undeleted.insert(n-1);

    vector<bool> del(n);
    for (int i = 0; i < s_i; ++i) {
        if (!inversions.empty()) {
            auto front = inversions.begin();
            int idx = *front;
            auto mid = undeleted.lower_bound(idx);
            if (mid != undeleted.begin() && mid != prev(undeleted.end(), 1)) {
                auto prv = prev(mid, 1);
                auto nxt = next(mid, 1);
                if (s[*prv] > s[*nxt]) {
                    inversions.insert(*prv);
                }
            }

            del[idx] = 1;
            undeleted.erase(mid);
            inversions.erase(front);
        } else {
            auto back = prev(undeleted.end(), 1);
            del[*back] = 1;
            undeleted.erase(back);
        }
    }

    for (int it = 0, i = 0; i < n; ++i) {
        if (del[i]) continue;
        if (it == real_index) {
            cout << s[i];
            return;
        }
        it++;
    }
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
