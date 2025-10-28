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

void solve()
{
    int n; cin >> n;
    vector<V2> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i].x >> p[i].y;
    }

    p.push_back(p[0]);
    n++;
    
    ll area = 0;
    for (int i = 1; i < n; ++i) {
        area += (p[i-1] * p[i]);
    }

    cout << abs(area) << '\n';
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

