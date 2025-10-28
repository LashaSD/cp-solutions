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

using v2f = ::_V2<double>;
using v2 = ::_V2<long long>;

using namespace std;
using ll = long long;

#define int ll

int min_dist(vector<v2>& x, vector<v2>& y)
{
    int n = x.size();
    if (n == 2) return (x[0] - x[1]).sqrLen();

    if (n == 3) {
        int a = (x[0] - x[1]).sqrLen();
        int b = (x[0] - x[2]).sqrLen();
        int c = (x[1] - x[2]).sqrLen();
        return min(a, min(b, c));
    }

    int mid = x.size() / 2;
    vector<v2> left_x(x.begin(), x.begin() + mid);
    vector<v2> right_x(x.begin() + mid, x.end());

    int mid_x = left_x.back().x;
    vector<v2> left_y, right_y;
    for (v2 p: y) {
        if (p.x <= mid_x) left_y.push_back(p);
        if (p.x >  mid_x) right_y.push_back(p);
    }
    
    int d = min(min_dist(left_x, left_y), min_dist(right_x, right_y));
    vector<v2> stripe;
    for (v2& p: y) {
        if ((p.x - mid_x)*(p.x - mid_x) < d) {
            stripe.push_back(p);
        }
    }

    for (int i = 0; i < (int) stripe.size(); ++i) {
        for (int j = i+1; j < (int) stripe.size() && j < i + 16; ++j) {
            d = min(d, (stripe[i] - stripe[j]).sqrLen());
        }
    }

    return d;
}

// Minimum Euclidean Distance
void solve()
{
    int n; cin >> n;
    vector<v2> by_x(n), by_y(n);
    for (int i = 0; i < n; ++i) {
        v2 p;
        cin >> p.x >> p.y;
        by_x[i] = p;
        by_y[i] = p;
    }

    sort(by_x.begin(), by_x.end(), [](v2& a, v2& b) {
                return make_pair(a.x, a.y) < make_pair(b.x, b.y);
            });

    sort(by_y.begin(), by_y.end(), [](v2& a, v2& b) {
                return make_pair(a.y, a.x) < make_pair(b.y, b.x);
            });

    cout << min_dist(by_x, by_y) << '\n';
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

