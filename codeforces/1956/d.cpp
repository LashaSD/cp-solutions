#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

vector<pair<int, int>> ans;

static inline ll sq(ll x) { return x*x; } 

bool zero[20];
void f(int l, int r)
{
    if (!zero[r]) {
        ans.push_back({r, r});
        zero[r] = 1;
    }

    if (l == r) return;

    f(l, r-1);
    ans.push_back({l, r});
    for (int k = l; k <= r; ++k) zero[k] = 0;
    f(l, r-1);
}

// 1956D: Nene and the Mex Operator
void solve()
{
    int n; cin >> n;
    vector<int> a(n+1), b(n+1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        b[i] = a[i];
    }

    vector<int> pref(n+1);
    for (int i = 1; i <= n; ++i) {
        pref[i] = pref[i-1] + a[i];
    }

    vector<int> dp(n+1), p(n+1);
    dp[0] = p[0] = 0;
    for (int i = 1; i <= n; ++i) {
        dp[i] = dp[i-1] + a[i];
        p[i] = -1;
        for (int l = i; l >= 1; --l) {
            int len = i - l + 1;
            if (dp[l-1] + sq(len) > dp[i]) {
                p[i] = l;
                dp[i] = dp[l-1] + sq(len);
            } 

            if (dp[l-1] + pref[i] - pref[l-1] > dp[i]) {
                dp[i] = dp[l-1] + pref[i] - pref[l-1];
                p[i] = -1;
            }
        }
    }

    int i = n;
    while (i >= 1) {
        while (i >= 1 && p[i] <= 0) i--;
        if (i >= 1) {
            for (int k = p[i]; k <= i; ++k)
                zero[k] = a[k] == 0;

            f(p[i], i);
            ans.push_back({p[i], i});
            i = p[i] - 1;
        }
    }

    cout << dp[n] << ' ' << ans.size() << '\n';
    for (auto [l, r]: ans) {
        cout << l << ' ' << r << '\n';
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
