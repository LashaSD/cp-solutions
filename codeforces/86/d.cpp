#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

using P = pair<int, int>;
int sum = 0;
const int maxV = 1e6 + 1;
int f[maxV + 1];
int block_size;

static inline void rem(int x) 
{
    sum -= f[x]*f[x]*x;
    f[x]--;
    sum += f[x]*f[x]*x;
}

static inline void add(int x) 
{
    sum -= f[x]*f[x]*x;
    f[x]++;
    sum += f[x]*f[x]*x;
}

static inline bool cmp(const pair<P,P>& a, const pair<P,P>& b)
{
    int ai = a.xx.xx / block_size;
    int bi = b.xx.xx / block_size;
    if (ai == bi) return a.xx.yy < b.xx.yy;
    return ai < bi;
}

// 86D: Powerful array
void solve()
{
    int n, t;
    cin >> n >> t;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<pair<P, P>> qvec;
    for (int i = 0; i < t; ++i) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        qvec.push_back({{l, r}, {i, 0}});
    }

    block_size = sqrt(n);
    sort(qvec.begin(), qvec.end(), cmp);

    sum = 0;

    vector<int> ans(t);
    int l = -1, r = -1;
    for (int i = 0; i < (int) qvec.size(); ++i) {
        auto [p1, p2] = qvec[i];
        auto [tl, tr] = p1;
        while (l > tl) {
            l--;
            add(a[l]);
        }

        while (l < tl) {
            if (l >= 0)
                rem(a[l]);
            l++;
        }

        while (r > tr) {
            rem(a[r]);
            r--;
        }

        while (r < tr) {
            r++;
            add(a[r]);
        }

        ans[qvec[i].yy.xx] = sum;
    }

    for (int i = 0; i < t; ++i) {
        cout << ans[i] << '\n';
    }
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
