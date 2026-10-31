#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pll = pair<ll, ll>;
constexpr ll INF = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
#define pb push_back

constexpr ll N = 1.1e7;

ll p[2 * N + 10];

int main()
{
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	string s;
	cin >> s;
	ll n = s.size();
	s = ' ' + s;
	string t = "";
	t += "!#";
	for (ll i = 1; i <= n; i++)
	{
		t += s[i];
		t += '#';
	}
	t += '@';
	ll m = t.size() - 2;
	ll c = 0, r = 0;
	ll ans = 0;
	for (ll i = 1; i <= m; i++)
	{
		if (i <= r)
		{
			p[i] = min(p[2 * c - i], r - i + 1);
		}
		else
		{
			p[i] = 1;
		}
		while (t[i - p[i]] == t[i + p[i]])
		{
			p[i]++;
		}
		if (i + p[i] - 1 > r)
		{
			c = i;
			r = i + p[i] - 1;
		}
		ans = max(ans, p[i] - 1);
	}
	cout << ans << "\n";
	return 0;
}
