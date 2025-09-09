#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;

typedef pair<ld, ld> Pt;

struct Line {
	ld a, b, c;
};

ld L_X(Line l, ld y)
{
	return (ld) (-l.c - (ld)l.b*(ld)y) / (ld) l.a;
}

ld L_Y(Line l, ld x)
{
	return (ld) (-l.c - (ld)l.a*(ld)x) / (ld) l.b;
}

ld dist(ld x1, ld y1, ld x2, ld y2)
{
	return sqrt((x1-x2)*(x1-x2) + (y2-y1)*(y2-y1));
}

// 1032D: Barcelonian Distance
void solve()
{
	Line l;
	cin >> l.a >> l.b >> l.c;

	ld x1, y1;
	cin >> x1 >> y1;

	ld x2, y2;
	cin >> x2 >> y2;

	ld dist_1 = abs(x2 - x1) + abs(y2 - y1);

	ld x, y;
	Pt cl_1 = {0.0, 0.0};
	x = L_X(l, y1);
	y = L_Y(l, x1);
	if ((x-x2)*(x-x2) + (y1-y2)*(y1-y2) < (x1-x2)*(x1-x2) + (y-y2)*(y-y2)) {
		cl_1 = {x, y1};
	} else {
		cl_1 = {x1, y};
	}

	Pt cl_2 = {0.0, 0.0};
	x = L_X(l, y2);
	y = L_Y(l, x2);
	if ((x-x1)*(x-x1) + (y1-y2)*(y1-y2) < (x1-x2)*(x1-x2) + (y-y1)*(y-y1)) {
		cl_2 = {x, y2};
	} else {
		cl_2 = {x2, y};
	}

	cout << setprecision(10) << fixed;
	cerr << setprecision(10) << fixed;

	ld dist_21 = fabs(cl_1.first - x1) + fabs(cl_1.second - y1);
	ld dist_22 = fabs(cl_2.first - x2) + fabs(cl_2.second - y2);
	ld dist_23 = dist(cl_1.first, cl_1.second, cl_2.first, cl_2.second);
	ld dist_2 = dist_21 + dist_22 + dist_23;
	
	//cerr << dist_21 << '\n';
	//cerr << dist_22 << '\n';
	//cerr << dist_23 << '\n';

	cout << min(dist_1, dist_2) << '\n';
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
