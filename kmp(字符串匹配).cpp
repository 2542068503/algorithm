#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pll = pair<ll, ll>;
constexpr ll INF = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
#define pb push_back

constexpr ll N = 1e6;

ll pi[N + 10];

int main()
{
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	string s, t;
	cin >> s >> t;
	ll n = (ll)s.size();
	ll m = (ll)t.size();
	s = " " + s;
	t = " " + t;
	for (ll i = 2, j = 0; i <= m; i++)
	{
		while (j && t[j + 1] != t[i])
		{
			j = pi[j];
		}
		if (t[j + 1] == t[i])
		{
			j++;
		}
		pi[i] = j;
	}
	for (ll i = 1, j = 0; i <= n; i++)
	{
		while (j && t[j + 1] != s[i])
		{
			j = pi[j];
		}
		if (t[j + 1] == s[i])
		{
			j++;
		}
		if (j == m)
		{
			cout << i - m + 1 << "\n";
			j = pi[j];
		}
	}
	for (ll i = 1; i <= m; i++)
	{
		cout << pi[i] << " ";
	}
	cout << "\n";
	return 0;
}
