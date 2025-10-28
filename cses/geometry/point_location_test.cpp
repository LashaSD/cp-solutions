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
    _V2 operator-(const _V2& other) const { return _V2(x - other.x, y - other.y); }
    T operator|(const _V2& other) const { return x * other.x + y * other.y; }
    T operator*(const _V2& other) const { return x * other.y - y * other.x; }
    T operator*(T k) const { return _V2(x * k, y * k); }
    T sqrLen() const { return (*this) | (*this); }
    _V2 normalize() const { return (*this) * (1 / sqrt(sqrLen())); }
};

using V2f = ::_V2<double>;
using V2 = ::_V2<int>;

using namespace std;
using ll = long long;
#define int ll

void solve()
{
    V2f a, b, c;
    cin >> a.x >> a.y;
    cin >> b.x >> b.y;
    cin >> c.x >> c.y;

    V2f dir = b - a;
    double res = dir * (c - a);
    if (res == 0) {
        cout << "TOUCH\n";
    } else if (res < 0) {
        cout << "RIGHT\n";
    } else {
        cout << "LEFT\n";
    }
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

