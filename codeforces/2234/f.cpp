#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <cstdint>
#include <set>
#include <cstdio>
#include <algorithm>
#include <functional>
#include <map>

#define assert(v) do { if (!(v)) { *(int*)0 = 0; } } while (0)

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2234F: Vessels, Heights and Two Versions (Hard Version)
void solve()
{
    int n; cin >> n;
    vector<int> vec(n);
    int mx = 0;
    int k = -1;
    for (int i = 0; i < n; ++i) {
        cin >> vec[i];
        mx = max(mx, vec[i]);
        if (vec[i] == mx) {
            k = i;
        }
    }

    vector<int> pref(n), suff(n);

    vector<pair<int, int>> st;
    int sum = 0;
    for (int i = (n + (k-1)) % n; i != k; i = (n + (i - 1)) % n) {
        int x = vec[i];
        int cnt = 1;
        while (st.size() > 0 && st.back().xx < x) {
            cnt += st.back().yy;
            sum -= st.back().xx * st.back().yy;
            st.pop_back();
        }
        st.push_back({x, cnt});
        sum += x * cnt;
        pref[i] = sum;
    }

    st.clear();
    sum = 0;
    for (int i = (k+1) % n; i != k; i = (i + 1) % n) {
        int x = vec[i];
        int cnt = 1;
        while (st.size() > 0 && st.back().xx < x) {
            cnt += st.back().yy;
            sum -= st.back().xx * st.back().yy;
            st.pop_back();
        }
        st.push_back({x, cnt});
        sum += x * cnt;
        suff[i] = sum;
    }

    for (int i = 0; i < n; ++i) {
        int l = (n + (i-1)) % n;
        cout << suff[l] + pref[i] << ' ';
    }
    cout << '\n';
}

int T = 1;
int32_t main(void)
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    cin >> T;
    while(T--)
        solve();

    return 0;
}
