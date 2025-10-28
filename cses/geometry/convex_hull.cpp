#include <iostream>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <map>

template <typename T>
struct _V2 {
    T x, y;
    _V2(T _x, T _y) : x(_x), y(_y) {}
    _V2() : x(0.0), y(0.0) {}
    _V2 operator+(const _V2& other) const { return _V2(x + other.x, y + other.y); }
    void operator+=(const _V2& other) { x += other.x, y += other.y; }
    _V2 operator-(const _V2& other) const { return _V2(x - other.x, y - other.y); }
    void operator-=(const _V2& other) { x -= other.x, y -= other.y; }
    bool operator<(const _V2& other) const { return std::make_pair(x, y) < std::make_pair(other.x, other.y); }
    T operator|(const _V2& other) const { return x * other.x + y * other.y; }
    T operator*(const _V2& other) const { return x * other.y - y * other.x; }
    T operator*(const T k) const { return _V2(x * k, y * k); }
    T sqrLen() const { return (*this) | (*this); }
};

using V2f = ::_V2<double>;
using V2 = ::_V2<long long>;

using namespace std;
using ll = long long;

#define int ll

void solve()
{
    int n; cin >> n;
    vector<V2> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i].x >> p[i].y;
    }
    sort(p.begin(), p.end());

    vector<V2> hull;
    for (int rep = 0; rep < 2; ++rep) {
        int sz = hull.size();
        for (int i = 0; i < n; ++i) {
            V2 c = p[i];
            while (hull.size() - sz >= 2) {
                V2 a = hull.end()[-2];
                V2 b = hull.end()[-1];
                if ((b - a) * (c - a) <= 0) {
                    break;
                }
                hull.pop_back();
            }

            hull.push_back(c);
        }

        hull.pop_back();
        reverse(p.begin(), p.end());
    }

    cout << hull.size() << '\n';
    for (V2 pt: hull) {
        cout << pt.x << ' ' << pt.y << '\n';
    }
    cout << '\n';
}

int T = 1;
int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // cin >> T;
    while(T--)
        solve();
    return 0;
}
