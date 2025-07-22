#include <bits/stdc++.h>
#include <cstdio>

#ifndef ONLINE_JUDGE
#include <dbg.h>
#else
#define dbg(...) (void)0
#endif

#define int ll

using namespace std;
using ll = long long;

// 1846F: Rudolph and Mimic
void solve()
{
    int n; cin >> n;
    vector<int> g_vec(n);
    map<int, vector<int>> g_pos;
    for (int i = 0; i < n; ++i) {
        int num; cin >> num;
        g_vec[i] = num;
        g_pos[num].push_back(i + 1);
    }

    int removed = 0;
    vector<int> vec = g_vec;
    map<int, vector<int>> pos = g_pos;

    auto read_objects = [&]() {
        int n = vec.size() - removed;
        vec.clear();
        pos.clear();
        for (int i = 0; i < n; ++i) {
            int num; cin >> num;
            vec.push_back(num);
            pos[num].push_back(i + 1);
        }
    };

    auto remove = [&](vector<int>& types) {
        vector<int> out;
        for (int t: types) {
            for (int p: pos[t])
                out.push_back(p);
        }
        removed = out.size();
        cout << "- " << removed << ' ';
        for (int p: out) cout << p << ' ';
        cout << endl;
        fflush(stdout);
    };

    auto diff = [&]() {
        int num = -1;
        for (const auto [x, vec_f] : pos) {
            // freaky of x has increased
            if (vec_f.size() > g_pos[x].size()) {
                num = x;
                break;
            }
        }

        return num;
    };

    // force change
    vector<int> types;
    remove(types);
    read_objects();
    // mimic changed to x
    int x = diff();
    if (x == -1) {
        remove(types);
        read_objects();
        x = diff();
    }
    int f = pos[x].size();
    // remove everything except x
    for (const auto it: pos) {
        if (it.first != x)
            types.push_back(it.first);
    }
    // force to change again
    remove(types);
    read_objects();
    if (pos[x].size() == f) {
        types.clear();
        remove(types);
        read_objects();
    }

    // the index of the object mimic changed to
    int idx = -1;
    for (int i = 0; i < vec.size(); ++i) {
        if (pos[vec[i]].size() == 1 && vec[i] != x) {
            idx = i;
            break;
        }
    }

    cout << "! " << idx+1 << endl;
    fflush(stdout);
}

int T = 1;
int32_t main(void)
{
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    cin >> T;
    while(T--)
        solve();
    return 0;
}
