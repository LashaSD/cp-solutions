#include <iostream>
#include <algorithm>
#include <vector>

template <typename T>
struct _V2 {
    T x, y;
    _V2(T _x, T _y) : x(_x), y(_y) {}
    _V2() : x(0.0), y(0.0) {}
    _V2 operator+(const _V2& other) const { return _V2(x + other.x, y + other.y); }
    _V2 operator-(const _V2& other) const { return _V2(x - other.x, y - other.y); }
    T operator|(const _V2& other) const { return x * other.x + y * other.y; }
    T operator*(const _V2& other) const { return x * other.y - y * other.x; }
    T sqrLen() const { return (*this) | (*this); }
};

using v2f = ::_V2<double>;

using namespace std;

void anchor_polygon(vector<v2f>& p)
{
    int idx = 0;
    for (size_t i = 0; i < p.size(); ++i) {
        if ((p[i].x < p[idx].x) ||
            (p[i].x == p[idx].x && p[i].y < p[idx].y)) 
        {
            idx = i;
        }
    }

    std::rotate(p.begin(), p.begin() + idx, p.end());
}

// vertices of the polygons should be ordered counter-clockwise
vector<v2f> minkowski(vector<v2f> P, vector<v2f> Q)
{
    anchor_polygon(P);
    anchor_polygon(Q);

    P.push_back(P[0]);
    Q.push_back(Q[0]);

    vector<v2f> res;
    res.reserve(P.size() + Q.size());

    size_t i = 0, j = 0;
    while (i < P.size() - 1 || j < Q.size() - 1) {
        res.push_back(P[i] + Q[j]);
        double cr = (P[i+1] - P[i]) * (Q[j+1] - Q[j]);

        if (cr >= 0 && i < P.size() - 1)
            i++;

        if (cr <= 0 && j < Q.size() - 1)
            j++;
    }

    return res;
}

int main(void)
{
    int n; cin >> n;
    vector<v2f> p(n);
    for (auto& pt: p)
        cin >> pt.x >> pt.y;

    int m; cin >> m;
    vector<v2f> q(n);
    for (auto& pt: q)
        cin >> pt.x >> pt.y;

    auto res = minkowski(p, q);
    for (auto pt: res) {
        cout << pt.x << ' ' << pt.y << '\n';
    }
    cout << '\n';
}
