#include <bits/stdc++.h>

using namespace std;
using ll = long long;

//#define STRESS

#define Pt pair<ll, ll>

static inline bool is_corner(Pt a)
{
    return (a.first + 1) % 3 == 0 && (a.second + 1) % 3 == 0;
}

struct Comparator {
    bool operator()(Pt a, Pt b) const {
        ll dist_1 = a.first + a.second;
        if (is_corner(a)) {
            dist_1 += 2;
        }

        ll dist_2 = b.first + b.second;
        if (is_corner(b)) {
            dist_2 += 2;
        }

        if (dist_1 == dist_2)
            return a < b;

        return dist_1 < dist_2;
    }
};

// 2090C: Dining Hall
void solve()
{
    int n; cin >> n;
    vector<int> vec(n);
    for (int& x: vec)
        cin >> x;

    set<Pt, Comparator> st;
    set<Pt, Comparator> free_st;
    
    map<Pt, bool> note;

    auto insert_table = [&](ll x, ll y) {
        if (note[make_pair(x, y)]) return;
        note[make_pair(x, y)] = true;

        st.insert({x  , y  });
        st.insert({x+1, y  });
        st.insert({x  , y+1});
        st.insert({x+1, y+1});

        free_st.insert({x, y});
    };

    auto insert_neig = [&](int x, int y) {
        insert_table(x + 3, y    );
        insert_table(x    , y + 3);
        insert_table(x + 3, y + 3);
    };


    insert_table(1, 1);
    insert_neig(1, 1);

    vector<Pt> ans(n);
    for (int i = 0; i < n; ++i) {
        bool t = vec[i];
        set<Pt, Comparator>::iterator it;
        if (t) {
            it = st.begin();
        } else {
            it = free_st.begin();
        }

        ll x = it->first;
        ll y = it->second;

        ll x1 = 3*(x / 3) + 1;
        ll y1 = 3*(y / 3) + 1;

        insert_neig(x1, y1);
        st.erase({x, y});
        free_st.erase({x, y});
        ans[i] = {x, y};
    }

#ifdef STRESS 
    const int MAX_N = 1e3;
    vector<vector<bool>> grid(MAX_N, vector<bool>(MAX_N));
    vector<Pt> loc_ans(n);
    for (int k = 0; k < n; ++k) {
        bool t = vec[k];
        Pt p = {INT_MAX/2, INT_MAX/2};
        for (int i = 0; i < MAX_N-2; ++i) {
            for (int j = 0; j < MAX_N-2; ++j) {
                int x = 3*(i / 3) + 1;
                int y = 3*(j / 3) + 1;
                if (i < x || i > x+1 || j > y+1 || j < y) continue;
                Pt loc_p = {i, j};

                if (!t) {
                    if (grid[x][y]     || 
                        grid[x+1][y+1] || 
                        grid[x+1][y]   || 
                        grid[x][y+1]) continue;
                }

                if (!grid[i][j]) {
                    ll dist_1 = p.first + p.second;
                    if (is_corner(p))
                        dist_1 += 2;

                    ll dist_2 = i + j;
                    if (is_corner(loc_p))
                        dist_2 += 2;

                    if (dist_2 < dist_1)
                        p = loc_p;
                    else if (dist_2 == dist_1)
                        p = min(p, loc_p);
                }
            }
        }

        grid[p.first][p.second] = 1;
        loc_ans[k] = p;
    }

    for (int i = 0; i < n; ++i) {
        if (ans[i] != loc_ans[i]) {
            cerr << "ERR: " << i << '\n';
            for (auto p: loc_ans) {
                cerr << p.first << ' ' << p.second << '\n';
            }
        }
        assert(ans[i] == loc_ans[i]);
    }
    cout << "OK\n";
#endif

#ifndef STRESS
    for (Pt p: ans)
        cout << p.first << ' ' << p.second << '\n';
#endif
}

void gen(char** argv)
{
    const int MAX_N = 10;
    srand(stoi(argv[1]));
    int n = rand() % (MAX_N + 1) + 1;
    cout << 1 << '\n';
    cout << n << '\n';
    for (int i = 0; i < n; ++i) {
        if (rand() % 2 == 0) {
            cout << 1 << ' ';
        } else {
            cout << 0 << ' ';
        }
    }
}

int T = 1;
int32_t main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

#ifdef STRESS
    if (argc == 2) {
        gen(argv);
        return 0;
    }
#endif

    cin >> T;
    while(T--)
        solve();
    return 0;
}
