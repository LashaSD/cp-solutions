#define _USE_MATH_DEFINES
#define TEST_PI M_PI

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
using V2 = ::_V2<int>;

template <typename T>
struct _V3 {
    T x, y, z;
    _V3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}
    _V3() : x(0.0), y(0.0), z(0.0) {}
    _V3 operator+(const _V3& other) const { return _V3(x + other.x, y + other.y, z + other.z); }
    _V3 operator-(const _V3& other) const { return _V3(x - other.x, y - other.y, z - other.z); }
    T operator|(const _V3& other) const { return x * other.x + y * other.y + z * other.z; }
    T operator*(const _V3& other) const { 
        return _V3((y*other.z) - (z*other.y), -((x * other.z) - (z * other.x)), (x * other.y) - (y * other.x));
    }
    T sqrLen() const { return (*this) | (*this); }
};

using V3f = ::_V3<double>;
using V3 = ::_V3<int>;
