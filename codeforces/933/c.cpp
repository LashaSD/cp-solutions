#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define Point pair<double, double>

const double INF = 1e9;
const double EPS = 1e-9;
inline bool eqd(double a, double b)
{ 
	return fabs(a - b) <= EPS; 
}

inline bool eqp(const Point &p1, const Point &p2)
{
    return eqd(p1.first, p2.first) && eqd(p1.second, p2.second);
}

// (x - .x)^2 + (y - .y)^2 = .r^2
struct Circle {
	double x, y, r;
};

// Ax + By + C = 0;
struct Line {
	double A, B, C;
};

array<Point, 2> circle_line(Circle a, Line b)
{
	array<Point, 2> ans = { make_pair(-INF, -INF), make_pair(-INF, -INF) };

	double A = b.A, B = b.B, C = b.C;
	double r = a.r;

	double d = fabs(-(double) C / sqrt(A*A + B*B));
	double qx = - A*C / (A*A + B*B);
	double qy = - B*C / (A*A + B*B);

	if (d == r) {
		ans[0] = make_pair(qx, qy);
	} else if (d < r) {
		double d1 = (r*r) - (C*C)/(A*A + B*B);
		double mult = sqrt(d1 / (A*A + B*B));
		double ax, ay, bx, by;

		ax = qx + B*mult;
		bx = qx - B*mult;
		ay = qy - A*mult;
		by = qy + A*mult;

		ans[0] = {ax, ay}; 
		ans[1] = {bx, by}; 
	}

	return ans;
}

array<Point, 2> circle_circle(Circle a, Circle b)
{
	array<Point, 2> ans = {make_pair(-INF, -INF), make_pair(-INF, -INF)};
	if (a.x == b.x && a.y == b.y) {
		if (a.r == b.r) {
			ans[0] = {INF, INF};
			ans[1] = {INF, INF};
		}

		return ans;
	}

	double cx = a.x, cy = a.y;
	double x2 = b.x - cx, y2 = b.y - cy;
	a.x = 0, a.y = 0;
	double r1 = a.r, r2 = b.r;
	Line l{ -2.0*x2, -2.0*y2, x2*x2 + y2*y2 + r1*r1 - r2*r2 };

	ans = circle_line(a, l);
	if (ans[0].first != -INF) {
		ans[0].first += cx;
		ans[0].second += cy;
	}

	if (ans[1].first != -INF) {
		ans[1].first += cx;
		ans[1].second += cy;
	}

	return ans;
}

inline int len(array<Point, 2> pts)
{
	return (pts[0].first != -INF) + (pts[1].first != -INF);
}

// 933C: A Colourful Prospect 
void solve()
{
	int n; cin >> n;
	vector<Circle> vec(n);
	for (Circle& c: vec)
		cin >> c.x >> c.y >> c.r;

	if (n == 1) {
		cout << 2 << '\n';
		return;
	} else if (n == 2) {
		Circle& a = vec[0];
		Circle& b = vec[1];
		auto x = circle_circle(a, b);
		int cnt = len(x);
		if (cnt == 1 || cnt == 0) {
			cout << 3 << '\n';
		} else {
			cout << 4 << '\n';
		}
		return;
	}

	vector<int> p(4);
	for (int i = 1; i <= 3; ++i)
		p[i] = i;

	function<int(int)> head = [&](int u) {
		if (p[u] == u) return u;
		return p[u] = head(p[u]);
	};

	for (int i = 0; i < n; ++i) {
		int u = (i + 1) % 3;
		int v = (i + 2) % 3;

		array<Point, 2> a = circle_circle(vec[i], vec[u]);
		array<Point, 2> b = circle_circle(vec[i], vec[v]);

		if (len(a) > 0) {
			p[head(i+1)] = head(u+1);
		}
		
		if (len(b) > 0) {
			p[head(i+1)] = head(v+1);
		}
	}

	set<int> components;
	for (int i = 1; i <= 3; ++i) {
		components.insert(head(p[i]));
	}

	int edges = 0;
	for (int i = 0; i < 3; ++i) {
		int u = (i + 1) % 3;
		int v = (i + 2) % 3;

		array<Point, 2> a = circle_circle(vec[i], vec[u]);
		array<Point, 2> b = circle_circle(vec[i], vec[v]);
		array<Point, 4> pts = { a[0], a[1], b[0], b[1] };

		vector<Point> uniq;
		for (int j = 0; j < 4; ++j) {
			if (pts[j].first == -INF || pts[j].second == -INF) continue;

			bool found = false;

			for (auto p: uniq) {
				if (eqp(pts[j], p)) found = true;
			}

			if (!found) {
				uniq.push_back(pts[j]);
			}
		}


		edges += uniq.size();
	}

	array<Point, 2> a = circle_circle(vec[0], vec[1]);
	array<Point, 2> b = circle_circle(vec[0], vec[2]);
	array<Point, 2> c = circle_circle(vec[1], vec[2]);
	array<Point, 6> pts = { a[0], a[1], b[0], b[1], c[0], c[1] };

	vector<Point> uniq;
	for (int i = 0; i < 6; ++i) {
		if (pts[i].first == -INF || pts[i].second == -INF) continue;

		bool found = false;
		for (auto p: uniq) {
			if (eqp(pts[i], p)) {
				found = true;
				break;
			}
		}

		if (!found) uniq.push_back(pts[i]);
	}

	int v = uniq.size();
	cout << edges - v + components.size() + 1 << '\n';
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
