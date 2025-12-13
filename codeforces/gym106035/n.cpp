#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

struct Node {
    int nxt[26];
    int f = 0;
    Node() {
        for (int i = 0; i < 26; ++i)
            nxt[i] = -1;
    };
};

void add_string(vector<Node>& tree, const string& s)
{
    int v = 0;
    for (int i = 0; i < (int) s.size(); ++i) {
        int j = s[i] - 'a';
        if (tree[v].nxt[j] == -1) {
            tree[v].nxt[j] = tree.size();
            tree.emplace_back();
        }
        v = tree[v].nxt[j];
        tree[v].f++;
    }
}

// GYM106035N: Auto-completion
void solve()
{
    int n; cin >> n;
    vector<Node> trie(1);
    string s; cin >> s;
    add_string(trie, s);
    for (int i = 0; i < n; ++i) {
        string s1; cin >> s1;
        add_string(trie, s1);
    }

    int ans = 0;
    int v = 0;
    bool tabbing = false;
    int i = 0, f1 = trie[trie[0].nxt[s[0] - 'a']].f;
    while (i < (int) s.size()) {
        int cnt = 0;
        for (int k = 0; k < 26; ++k) {
            if (trie[v].nxt[k] != -1) {
                cnt++;
            }
        }

        bool type = 0;
        if (trie[trie[v].nxt[s[i] - 'a']].f != f1) {
            f1 = trie[trie[v].nxt[s[i] - 'a']].f;
            type = 1;
        }

        if (cnt > 1) {
            type = 1;
        }

        if (type) {
            cerr << "TYPE: " << i << '\n';
            ans++;
            tabbing = 0;
        } else if (!tabbing) {
            cerr << "TAB: " << i << '\n';
            tabbing = 1;
            ans++;
        }

        v = trie[v].nxt[s[i] - 'a'];
        i++;
    }
    
    cout << ans << '\n';
}

int T = 1;
int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //cin >> T;
    while(T--)
        solve();

    return 0;
}
