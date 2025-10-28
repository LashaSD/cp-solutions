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

static inline bool inter(int a, int b, int c, int d)
{
    if (a > b) swap(a, b);
    if (c > d) swap(c, d);
    return max(a, c) <= min(b, d);
}

void solve()
{
    V2 a, b, c, d;
    cin >> a.x >> a.y;
    cin >> b.x >> b.y;
    cin >> c.x >> c.y;
    cin >> d.x >> d.y;

    if ((b - a) * (d - c) == 0) {
        if ((b - a) * (c - a) != 0) {
            cout << "NO\n";
            return;
        }

        if (inter(a.x, b.x, c.x, d.x) && inter(a.y, b.y, c.y, d.y)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
        return;
    }

    auto abxac = (b - a) * (c - a);
    auto abxad = (b - a) * (d - a);
    
    auto cdxcb = (d - c) * (b - c);
    auto cdxca = (d - c) * (a - c);

    if ((abxac > 0 && abxad > 0) || (abxac < 0 && abxad < 0)) {
        cout << "NO\n";
        return;
    }

    if ((cdxcb > 0 && cdxca > 0) || (cdxcb < 0 && cdxca < 0)) {
        cout << "NO\n";
        return;
    }

    cout << "YES\n";
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

