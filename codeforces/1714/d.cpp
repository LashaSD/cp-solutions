#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

using namespace std;
using ll = long long;

struct Node {
    int next[26], id = -1;

    Node() {
        fill(begin(next), end(next), -1);
    }
};

void add_string(vector<Node>& trie, string const& s, int str_id) {
    int v = 0;
    for (char ch : s) {
        int c = ch - 'a';
        if (trie[v].next[c] == -1) {
            trie[v].next[c] = (int) trie.size();
            trie.emplace_back();
        }
        v = trie[v].next[c];
    }
    trie[v].id = str_id;
}

// D. Color with Occurrences
void solve()
{
    string s; cin >> s;
    int n; cin >> n;
    vector<Node> trie(1);
    vector<int> dp(s.size());
    vector<pair<int, pair<int, int>>> ans(1200, {-1, {-1, -1}});

    for (int i = 0; i < n; ++i) {
        string str; cin >> str;
        add_string(trie, str, i);
    }

    // fill(begin(dp), end(dp), INT_MAX);
    for (size_t i = 0; i < s.size(); ++i) {
        int ops = 0;
        if (i != 0) {
            ops = dp[i-1];
        }

        {
            int u = 0;
            int best_str_id = -1;
            size_t best_str_end = -1;
            for (size_t j = i; j < s.size(); ++j) {
                if (trie[u].next[s[j]-'a'] == -1) break;

                u = trie[u].next[s[j]-'a'];
                if (trie[u].id != -1) {
                    best_str_id = trie[u].id;
                    best_str_end = j;
                }
            }

            if (best_str_id != -1) {
                if (ans[ops+1].first < (int) best_str_end) {
                    ans[ops+1] = { (int) best_str_end, { i, best_str_id } };
                }

                for (size_t j = i; j <= best_str_end; ++j) {
                    dp[j] = min(dp[j], ops+1);
                }
            }
        }

        if (dp[i] == INT_MAX) {
            cout << -1 << '\n';
            return;
        }
    }

    cout << dp[s.size()-1] << '\n';
    for (int i = 1; i <= dp[s.size()-1]; ++i) {
        cout << ans[i].second.second+1 << ' ' << ans[i].second.first+1 << '\n';
    }
}

int T = 1;
int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // scanf("%d", &T);
    cin >> T;
    while(T--)
        solve();
    return 0;
}
