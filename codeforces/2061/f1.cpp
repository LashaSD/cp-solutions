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

void fill_pref(vector<int>& pref, vector<pair<char, pair<int, int>>>& blocks, char c, bool count=false)
{
    int i = 1;
    for (int j = 0; j < (int) blocks.size(); ++j) {
        if (blocks[j].first != c) continue;

        int l = blocks[j].second.first + 1; 
        int r = blocks[j].second.second + 1; 

        while (i < l) {
            pref[i] = pref[i-1];
            i++;
        }

        int v = pref[l - 1] + (r - l + 1);
        if (count) {
            v = pref[l - 1] + 1;
        }

        while (i <= r) {
            pref[i] = v;
            i++;
        }
    }
    
    int val = pref[i-1];
    for (; i < (int) pref.size(); ++i) {
        pref[i] = val;
    }
}

// 2061F1: Kevin and Binary String (Easy Version)
void solve()
{
    string s, t;
    cin >> s >> t;
    int n = s.size();

    vector<pair<char, pair<int, int>>> b_s = {{s[0], {0, 0}}}, b_t = {{t[0], {0, 0}}};
    for (int i = 1; i < n; ++i) {
        if (s[i] == s[i-1]) {
            b_s.back().second.second = i;
        } else {
            b_s.push_back({s[i], {i, i}});
        }
    }

    for (int i = 1; i < n; ++i) {
        if (t[i] == t[i-1]) {
            b_t.back().second.second = i;
        } else {
            b_t.push_back({t[i], {i, i}});
        }
    }

    vector<int> ps0(n+1), ps1(n+1);
    fill_pref(ps0, b_s, '0');
    fill_pref(ps1, b_s, '1');

    vector<int> cntps0(n+1), cntps1(n+1);
    fill_pref(cntps0, b_s, '0', true);
    fill_pref(cntps1, b_s, '1', true);

    //for (int i = 1; i <= n; ++i)
    //    cerr << cntps0[i] << ' ';
    //cerr << '\n';
    //for (int i = 1; i <= n; ++i)
    //    cerr << ps1[i] << ' ';
    //cerr << '\n';

    int i = 0, j = 0;
    int ops = 0;
    while (i < (int) b_s.size() && j < (int) b_t.size()) {
        auto& bs = b_s[i];
        auto& bt = b_t[j];
        
        char c1 = bs.first;
        int l1 = bs.second.first;
        int r1 = bs.second.second;

        char c2 = bt.first;
        int l2 = bt.second.first;
        int r2 = bt.second.second;

        // cerr << "BLK: " << c1 << ' ' << l1 << ' ' << r1 << '\n';

        int diff = 0;
        if (c1 != c2) {
            if (c2 == '?') {
                if (r2 > r1) {
                    i++;
                } else {
                    bs.second.first = r1 + 1;
                    j++;
                    continue;
                }
            } else {
                diff = r2 - l2 + 1;
            }
        } else {
            if (r2 >= r1) {
                diff = r2 - r1;
            } else {
                if ((j + 1) >= (int) b_t.size() || b_t[j+1].first != '?') {
                    cout << -1 << '\n';
                    return;
                }
            }
        }

        if (diff == 0) {
            i++, j++;
        } else if (diff > 0) {
            if (c2 == '1') {
                int value = ps1[r1 + 1] + diff;
                auto it = lower_bound(ps1.begin(), ps1.end(), value);
                if (it != ps1.end()) {
                    int x = *it;
                    if (x > value) {
                        int dx = x - value;
                        if ((j + 1) > (int) b_t.size() || b_t[j+1].first != '?' || (b_t[j+1].second.second - b_t[j+1].second.first + 1) < dx) {
                            cout << -1 << '\n';
                            return;
                        }
                    }
                } else {
                    cout << -1 << '\n';
                    return;
                }

                int idx = it - ps1.begin() - 1;
                int cnt1 = cntps1[idx + 1] - cntps1[r1 + 1];
                int cnt0 = cntps0[idx + 1] - cntps0[r1 + 1];
                i += cnt1 + cnt0;

                // cerr << "DBG: " << idx << ' ' << ps1[r1 + 1] + diff << '\n';

                ops += cnt1;
                if ((i + 1) < (int) b_s.size()) {
                    i++;
                    b_s[i].second.first -= cnt0;
                } else {
                    b_s[i].first = '0';
                    b_s[i].second.first -= cnt0;
                }

                j++;
            } else {
                int value = ps0[r1 + 1] + diff;
                auto it = lower_bound(ps0.begin(), ps0.end(), value);
                if (it != ps0.end()) {
                    int x = *it;
                    if (x > value) {
                        int dx = x - value;
                        if ((j + 1) > (int) b_t.size() || b_t[j+1].first != '?' || (b_t[j+1].second.second - b_t[j+1].second.first + 1) < dx) {
                            //cerr << b_t[j+1].second.second -  b_t[j+1].second.first + 1 << ' ' << dx << '\n';
                            cout << -1 << '\n';
                            return;
                        }
                    }
                } else {
                    cout << -1 << '\n';
                    return;
                }

                int idx = it - ps0.begin() - 1;
                int cnt1 = cntps1[idx + 1] - cntps1[r1 + 1];
                int cnt0 = cntps0[idx + 1] - cntps0[r1 + 1];
                i += cnt1 + cnt0;

                ops += cnt0;
                if ((i + 1) < (int) b_s.size()) {
                    i++;
                    b_s[i].second.first -= cnt1;
                } else {
                    b_s[i].first = '1';
                    b_s[i].second.first -= cnt1;
                }
                j++;
            }
        }
    }

    //cerr << "ANS: ";
    cout << ops << '\n';
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
