#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
const ll INF = 1e18;
mt19937 rnd((unsigned int)chrono::steady_clock::now().time_since_epoch().count());
#define pb push_back

constexpr ll N = 1e4;

ll n, k;
ll cen;
ll vis[N + 10];
ll sz[N + 10];
ll maxsz[N + 10];
vector<ll> tmp;
vector<ll> used;
vector<pair<ll, ll>> g[N + 10];
ll ans;
ll totsz;

void getcen(ll u, ll f)
{
	sz[u] = 1;
	maxsz[u] = 0;
	for (auto p : g[u])
	{
		ll v = p.first;
		if (v == f || vis[v])
		{
			continue;
		}
		getcen(v, u);
		sz[u] += sz[v];
		maxsz[u] = max(maxsz[u], sz[v]);
	}
	maxsz[u] = max(totsz - sz[u], maxsz[u]);
	if (!cen || maxsz[u] < maxsz[cen])
	{
		cen = u;
	}
}

void getsz(ll u, ll f)
{
	totsz++;
	for (auto p : g[u])
	{
		ll v = p.first;
		if (v == f || vis[v])
		{
			continue;
		}
		getsz(v, u);
	}
}

void getdis(ll u, ll f, ll d)
{
	tmp.pb(d);
	for (auto p : g[u])
	{
		ll v = p.first, w = p.second;
		if (v == f || vis[v])
		{
			continue;
		}
		getdis(v, u, d + w);
	}
}

void calc(ll u)
{
	used.pb(0);
	for (auto p : g[u])
	{
		ll v = p.first, w = p.second;
		if (vis[v])
		{
			continue;
		}
		tmp.clear();
		getdis(v, u, w);
		sort(tmp.begin(), tmp.end());
		ll r = used.size() - 1;
		for (ll i = 0; i < (ll)tmp.size(); i++)
		{
			while (r >= 0 && used[r] + tmp[i] > k)
			{
				r--;
			}
			if (r < 0)
			{
				break;
			}
			ans += r + 1;
		}

		ll tn = tmp.size(), tm = used.size();
		vector<ll> nxtused;
		nxtused.reserve(tn + tm);
		ll i = 0, j = 0;
		while (i < tn && j < tm)
		{
			nxtused.pb((tmp[i] < used[j]) ? tmp[i++] : used[j++]);
		}
		while (i < tn)
		{
			nxtused.pb(tmp[i++]);
		}
		while (j < tm)
		{
			nxtused.pb(used[j++]);
		}
		used = move(nxtused);
	}
	used.clear();
}

void solve(ll u)
{
	vis[u] = 1;
	calc(u);
	for (auto p : g[u])
	{
		ll v = p.first;
		if (vis[v])
		{
			continue;
		}
		totsz = 0;
		getsz(v, 0);
		cen = 0;
		getcen(v, 0);
		solve(cen);
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n >> k)
	{
		if (n == 0 && k == 0)
		{
			break;
		}
		memset(vis, 0, sizeof(vis));
		used.clear();
		for (ll i = 1; i <= n; i++)
		{
			g[i].clear();
		}
		ans = 0;

		for (ll i = 1; i < n; i++)
		{
			ll u, v, l;
			cin >> u >> v >> l;
			g[u].pb({v, l});
			g[v].pb({u, l});
		}
		totsz = n;
		cen = 0;
		getcen(1, 0);
		solve(cen);
		cout << ans << "\n";
	}
	return 0;
}
