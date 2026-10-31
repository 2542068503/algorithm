#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pll = pair<ll, ll>;
constexpr ll INF = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
#define pb push_back

constexpr ll N = 2e4, M = 1e5;

vector<ll> g[N + 10];
ll dfn[N + 10];
ll low[N + 10];
ll tdfn;
ll vcc_cnt;
ll vcc_id[N + 10];
stack<ll> stk;
bool cut[N + 10];
vector<ll> vcc[N + 10];

void tarjan(ll u, ll f)
{
	dfn[u] = low[u] = ++tdfn;
	stk.push(u);
	ll child = 0;
	for (ll v : g[u])
	{
		if (v == f)
		{
			continue;
		}
		if (!dfn[v])
		{
			child++;
			tarjan(v, u);
			low[u] = min(low[u], low[v]);
			if (low[v] >= dfn[u])
			{
				if (f != 0)
				{
					cut[u] = 1;
				}
				vcc_cnt++;
				while (1)
				{
					ll x = stk.top();
					stk.pop();
					vcc[vcc_cnt].pb(x);
					if (x == v)
					{
						break;
					}
				}
				vcc[vcc_cnt].pb(u);
			}
		}
		else
		{
			low[u] = min(low[u], dfn[v]);
		}
	}
	if (f == 0 && child >= 2)
	{
		cut[u] = 1;
	}
	if (f == 0 && child == 0)
	{
		vcc[++vcc_cnt].pb(u);
	}
}

int main()
{
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	ll n, m;
	cin >> n >> m;
	for (ll i = 1; i <= m; i++)
	{
		ll u, v;
		cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}
	for (ll i = 1; i <= n; i++)
	{
		if (!dfn[i])
		{
			tarjan(i, 0);
		}
	}
	vector<ll> ans;
	for (ll i = 1; i <= n; i++)
	{
		if (cut[i])
		{
			ans.pb(i);
		}
	}
	cout << (ll)ans.size() << "\n";
	for (ll i : ans)
	{
		cout << i << " ";
	}
	cout << "\n";
	return 0;
}
