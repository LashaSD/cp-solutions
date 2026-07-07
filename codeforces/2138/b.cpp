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

#define assert(v) do { if (!(v)) { __builtin_trap(); } } while (0)

using namespace std;
using ll = long long;

#define int ll
#define xx first
#define yy second

// 2138B: Antiamuny Wants to Learn Swap 
void solve()
{
    int n, q;
    cin >> n >> q;
    vector<int> vec(n);
    for (int i = 0; i < n; ++i) {
        cin >> vec[i];
    }

    vector<int> left(n, -1), right(n, -1);
    vector<int> st;
    for (int i = 0; i < n; ++i) {
        int x = vec[i];
        while (st.size() > 0 && vec[st.back()] < x) {
            st.pop_back();
        }

        if (st.size() > 0) {
            left[i] = st.back();
        }

        st.push_back(i);
    }

    st.clear();
    for (int i = n-1; i >= 0; --i) {
        int x = vec[i];
        while (st.size() > 0 && vec[st.back()] > x) {
            st.pop_back();
        }

        if (st.size() > 0) {
            right[i] = st.back();
        }

        st.push_back(i);
    }

    const int inf = 1e9;
    vector<int> mn_right(n, inf);
    for (int i = 0; i < n; ++i) {
         if (left[i] != -1 && right[i] != -1) {
            mn_right[left[i]] = min(mn_right[left[i]], right[i]);
         }
    }

    for (int i = n-2; i >= 0; --i) {
        mn_right[i] = min(mn_right[i], mn_right[i+1]);
    }


    for (int qi = 0; qi < q; ++qi) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        if (mn_right[l] <= r) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
        }
    }

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
