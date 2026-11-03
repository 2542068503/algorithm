#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pll = pair<ll, ll>;
constexpr ll INF = (ll)1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
#define pb push_back

constexpr ll N = 1e5;

struct fhq
{
	ll ls, rs;
	ll val, sz;
	ull rd;
} tr[N + 10];

ll tot, rt;

ll addnode(ll val)
{
	ll u = ++tot;
	tr[u].ls = tr[u].rs = 0;
	tr[u].val = val;
	tr[u].sz = 1;
	tr[u].rd = rnd();
	return u;
}

void pushup(ll u)
{
	tr[u].sz = tr[tr[u].ls].sz + tr[tr[u].rs].sz + 1;
}

void split(ll u, ll val, ll &x, ll &y)
{
	if (!u)
	{
		x = 0, y = 0;
		return ;
	}
	if (tr[u].val <= val)
	{
		x = u;
		split(tr[u].rs, val, tr[u].rs, y);
	}
	else
	{
		y = u;
		split(tr[u].ls, val, x, tr[u].ls);
	}
	pushup(u);
}

ll merge(ll u, ll v)
{
	if (!u || !v)
	{
		return u + v;
	}
	if (tr[u].rd < tr[v].rd)
	{
		tr[u].rs = merge(tr[u].rs, v);
		pushup(u);
		return u;
	}
	else
	{
		tr[v].ls = merge(u, tr[v].ls);
		pushup(v);
		return v;
	}
}

void insert(ll val)
{
	ll y = addnode(val);
	ll x = 0, z = 0;
	split(rt, val, x, z);
	rt = merge(merge(x, y), z);
}

void del(ll val)
{
	ll x = 0, y = 0, z = 0;
	split(rt, val, x, z);
	split(x, val - 1, x, y);
	if (y)
	{
		y = merge(tr[y].ls, tr[y].rs);
	}
	rt = merge(merge(x, y), z);
}

ll queryrk(ll val)
{
	ll x = 0, y = 0;
	split(rt, val - 1, x, y);
	ll ans = tr[x].sz + 1;
	rt = merge(x, y);
	return ans;
}

ll queryval(ll val)
{
	ll u = rt;
	while (u)
	{
		if (tr[tr[u].ls].sz + 1 == val)
		{
			return tr[u].val;
		}
		else if (tr[tr[u].ls].sz + 1 < val)
		{
			val -= (tr[tr[u].ls].sz + 1);
			u = tr[u].rs;
		}
		else
		{
			u = tr[u].ls;
		}
	}
	return -INF;
}

ll querypre(ll val)
{
	ll u = rt, ans = -INF;
	while (u)
	{
		if (tr[u].val < val)
		{
			ans = tr[u].val;
			u = tr[u].rs;
		}
		else
		{
			u = tr[u].ls;
		}
	}
	return ans;
}

ll querysuf(ll val)
{
	ll u = rt, ans = INF;
	while (u)
	{
		if (tr[u].val > val)
		{
			ans = tr[u].val;
			u = tr[u].ls;
		}
		else
		{
			u = tr[u].rs;
		}
	}
	return ans;
}

int main()
{
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);

	ll n;
	cin >> n;
	for (ll i = 1; i <= n; i++)
	{
		ll opt, x;
		cin >> opt >> x;
		if (opt == 1)
		{
			insert(x);
		}
		else if (opt == 2)
		{
			del(x);
		}
		else if (opt == 3)
		{
			cout << queryrk(x) << "\n";
		}
		else if (opt == 4)
		{
			cout << queryval(x) << "\n";
		}
		else if (opt == 5)
		{
			cout << querypre(x) << "\n";
		}
		else
		{
			cout << querysuf(x) << "\n";
		}
	}
	return 0;
}
