#include <bits/stdc++.h>

using namespace std;
using ll = long long;

bool ok(vector<pair<ll, ll>> vec, pair<ll, ll> size)
{
	// { width, height }
	multiset<pair<ll, ll>> w_st;

	// { height, width }
	multiset<pair<ll, ll>> h_st;

	for (auto p: vec) {
		w_st.insert({p.second, p.first});
		h_st.insert(p);
	}

	pair<ll, ll> rect = size;
	while (h_st.size() > 0 && rect.first > 0 && rect.second > 0) {
		auto h_it = prev(h_st.end());
		auto w_it = prev(w_st.end());

		ll h = h_it->first;
		ll w = w_it->first;

		if (h == rect.first) {
			rect.second -= h_it->second;
			w_st.erase(w_st.find({h_it->second, h_it->first}));
			h_st.erase(h_it);
		} else if (w == rect.second) {
			rect.first -= w_it->second;
			h_st.erase(h_st.find({w_it->second, w_it->first}));
			w_st.erase(w_it);
		} else {
			break;
		}
	}

	return rect.first == 0 || rect.second == 0;
}

// 1918B: The Butcher 
void solve()
{
	ll n; cin >> n;
	// {height, width}
	vector<pair<ll, ll>> vec(n);
	for (auto& p: vec)
		cin >> p.first >> p.second;

	ll area = 0;
	for (auto p: vec) { 
		ll h = p.first, w = p.second;
		area += w*h;
	}

#ifndef ONLINE_JUDGE
	//sort(vec.begin(), vec.end());
	//cerr << "AREA: " << area << '\n';
	//cerr << "VEC:\n";
	//for (auto p: vec)
	//	cerr << "H: " << p.first << " W: " << p.second << '\n';
#endif // ONLINE_JUDGE

	pair<ll, ll> w_cut = {0, 0}, h_cut = {0, 0};
	for (auto p: vec) {
		int h = p.first, w = p.second;
		if ((w > w_cut.second) ||
			(w == w_cut.second && h > w_cut.first))
		{
			w_cut = p;
		}

		if ((h > h_cut.first) ||
			(h == h_cut.first && w > h_cut.second))
		{
			h_cut = p;
		}
	}

	// fill in horizontal cut rect
	ll w_cut_area = w_cut.first * w_cut.second;
	ll w_cut_leftover = (area - w_cut_area);
	w_cut.first += w_cut_leftover / w_cut.second;

	// fill in vertical cut rect
	ll h_cut_area = h_cut.first * h_cut.second;
	ll h_cut_leftover = area - h_cut_area;
	h_cut.second += h_cut_leftover / h_cut.first;

	if (w_cut.first * w_cut.second != area) {
		cout << 1 << '\n';
		cout << h_cut.first << ' ' << h_cut.second << '\n';
		return;
	} else if (h_cut.first * h_cut.second != area) {
		cout << 1 << '\n';
		cout << w_cut.first << ' ' << w_cut.second << '\n';
		return;
	}

#ifndef ONLINE_JUDGE
	// cerr << "W_CUT: H: " << w_cut.first << " W:" << w_cut.second << '\n';
	// cerr << "H_CUT: H: " << h_cut.first << " W:" << h_cut.second << '\n';
#endif // ONLINE_JUDGE

	vector<pair<ll, ll>> ans;
	if (ok(vec, w_cut))
		ans.push_back(w_cut);

	if (ok(vec, h_cut))
		ans.push_back(h_cut);

	if (w_cut == h_cut) {
		cout << 1 << '\n';
		cout << w_cut.first << ' ' << w_cut.second << '\n';
	} else {
		cout << ans.size() << '\n';
		for (auto p: ans)
			cout << p.first << ' ' << p.second << '\n';
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
