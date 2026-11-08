#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pll = pair<ll, ll>;
constexpr ll INF = (ll)1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
#define pb push_back

constexpr ll N = 100000;

struct Node
{
	ll ch[2];
	ll fa;
	ll val;
	ll cnt;
	ll sz;
} tr[N + 10];

ll rt, tot;

void pushup(ll x)
{
	tr[x].sz = tr[tr[x].ch[0]].sz + tr[tr[x].ch[1]].sz + tr[x].cnt;
}

bool dir(ll x)
{
	return tr[tr[x].fa].ch[1] == x;
}

void rotate(ll x)
{
	ll y = tr[x].fa, z = tr[y].fa;
	ll k = dir(x);
	tr[y].ch[k] = tr[x].ch[k ^ 1];
	if (tr[x].ch[k ^ 1])
	{
		tr[tr[x].ch[k ^ 1]].fa = y;
	}
	tr[x].ch[k ^ 1] = y;
	if (z)
	{
		tr[z].ch[tr[z].ch[1] == y] = x;
	}
	tr[y].fa = x;
	tr[x].fa = z;
	pushup(y);
	pushup(x);
}

void splay(ll x, ll goal = 0)
{
	while (tr[x].fa != goal)
	{
		ll p = tr[x].fa, g = tr[p].fa;
		if (g != goal)
		{
			if (dir(x) == dir(p))
			{
				rotate(p);
			}
			else
			{
				rotate(x);
			}
		}
		rotate(x);
	}
	if (!goal)
	{
		rt = x;
	}
}

ll newNode(ll v, ll p)
{
	tot++;
	tr[tot].val = v;
	tr[tot].cnt = 1;
	tr[tot].sz = 1;
	tr[tot].fa = p;
	tr[tot].ch[0] = 0;
	tr[tot].ch[1] = 0;
	return tot;
}

void init()
{
	rt = newNode(-INF, 0);
	tr[rt].ch[1] = newNode(INF, rt);
	pushup(rt);
}

void insert(ll v)
{
	ll u = rt, p = 0;
	while (u && tr[u].val != v)
	{
		p = u;
		u = tr[u].ch[v > tr[u].val];
	}
	if (u)
	{
		tr[u].cnt++;
		pushup(u);
	}
	else
	{
		u = newNode(v, p);
		if (p)
		{
			tr[p].ch[v > tr[p].val] = u;
		}
	}
	splay(u);
}

void del(ll v)
{
	ll u = rt;
	while (u && tr[u].val != v)
	{
		u = tr[u].ch[v > tr[u].val];
	}
	if (!u)
	{
		return;
	}
	splay(u);
	if (tr[u].cnt > 1)
	{
		tr[u].cnt--;
		pushup(u);
		return;
	}
	ll p = tr[u].ch[0];
	while (tr[p].ch[1])
	{
		p = tr[p].ch[1];
	}
	ll s = tr[u].ch[1];
	while (tr[s].ch[0])
	{
		s = tr[s].ch[0];
	}
	splay(p, 0);
	splay(s, p);
	tr[s].ch[0] = 0;
	pushup(s);
	pushup(p);
}

ll getRank(ll v)
{
	ll u = rt, res = 0, last = 0;
	while (u)
	{
		last = u;
		if (v <= tr[u].val)
		{
			u = tr[u].ch[0];
		}
		else
		{
			res += tr[tr[u].ch[0]].sz + tr[u].cnt;
			u = tr[u].ch[1];
		}
	}
	splay(last);
	return res;
}

ll getKth(ll k)
{
	ll u = rt;
	while (u)
	{
		if (tr[u].ch[0] && k <= tr[tr[u].ch[0]].sz)
		{
			u = tr[u].ch[0];
		}
		else
		{
			ll tmp = tr[tr[u].ch[0]].sz + tr[u].cnt;
			if (k <= tmp)
			{
				splay(u);
				return tr[u].val;
			}
			k -= tmp;
			u = tr[u].ch[1];
		}
	}
	return 0;
}

ll getPre(ll v)
{
	ll u = rt, ans = -INF, last = 0;
	while (u)
	{
		last = u;
		if (tr[u].val < v)
		{
			ans = max(ans, tr[u].val);
			u = tr[u].ch[1];
		}
		else
		{
			u = tr[u].ch[0];
		}
	}
	splay(last);
	return ans;
}

ll getNxt(ll v)
{
	ll u = rt, ans = INF, last = 0;
	while (u)
	{
		last = u;
		if (tr[u].val > v)
		{
			ans = min(ans, tr[u].val);
			u = tr[u].ch[0];
		}
		else
		{
			u = tr[u].ch[1];
		}
	}
	splay(last);
	return ans;
}

int main()
{
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	init();
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
			cout << getRank(x) << "\n";
		}
		else if (opt == 4)
		{
			cout << getKth(x + 1) << "\n";
		}
		else if (opt == 5)
		{
			cout << getPre(x) << "\n";
		}
		else if (opt == 6)
		{
			cout << getNxt(x) << "\n";
		}
	}
	return 0;
}
