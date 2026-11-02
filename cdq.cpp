#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pll = pair<ll, ll>;
constexpr ll INF = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
#define pb push_back

constexpr ll N = 2e5;

struct node
{
	ll a, b, c, cnt, res;
	bool operator < (const node &cmp) const
	{
		if (a != cmp.a)
		{
			return a < cmp.a;
		}
		else if (b != cmp.b)
		{
			return b < cmp.b;
		}
		else
		{
			return c < cmp.c;
		}
	}
	bool operator == (const node &cmp) const
	{
		return a == cmp.a && b == cmp.b && c == cmp.c;
	}
} s[N + 10], tmp[N + 10];

ll tr[N + 10];
ll ans[N + 10];

void add(ll pos, ll val)
{
	for (; pos <= N; pos += (pos & -pos))
	{
		tr[pos] += val;
	}
}

ll query(ll pos)
{
	ll res = 0;
	for (; pos > 0; pos -= (pos & -pos))
	{
		res += tr[pos];
	}
	return res;
}

void cdq(ll l, ll r)
{
	if (l == r)
	{
		return ;
	}
	ll mid = l + (r - l) / 2;
	cdq(l, mid);
	cdq(mid + 1, r);
	ll j = l;
	for (ll i = mid + 1; i <= r; i++)
	{
		while (j <= mid && s[j].b <= s[i].b)
		{
			add(s[j].c, s[j].cnt);
			j++;
		}
		s[i].res += query(s[i].c);
	}
	for (ll i = l; i < j; i++)
	{
		add(s[i].c, -s[i].cnt);
	}

	ll p1 = l, p2 = mid + 1, k = l;
	while (p1 <= mid && p2 <= r)
	{
		if (s[p1].b <= s[p2].b)
		{
			tmp[k++] = s[p1++];
		}
		else
		{
			tmp[k++] = s[p2++];
		}
	}
	while (p1 <= mid)
	{
		tmp[k++] = s[p1++];
	}
	while (p2 <= r)
	{
		tmp[k++] = s[p2++];
	}
	for (ll i = l; i <= r; i++)
	{
		s[i] = tmp[i];
	}
}

int main()
{
//	freopen(".in", "r", stdin);
//	freopen(".out", "cnt", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	ll n, k;
	cin >> n >> k;
	for (ll i = 1; i <= n; i++)
	{
		cin >> s[i].a >> s[i].b >> s[i].c;
		s[i].cnt = 1;
	}
	sort(s + 1, s + n + 1);
	ll m = 1;
	for (ll i = 2; i <= n; i++)
	{
		if (s[i] == s[m])
		{
			s[m].cnt++;
		}
		else
		{
			s[++m] = s[i];
		}
	}
	cdq(1, m);
	for (ll i = 1; i <= m; i++)
	{
		ans[s[i].res + s[i].cnt - 1] += s[i].cnt;
	}
	for (ll i = 1; i <= n; i++)
	{
		cout << ans[i - 1] << "\n";
	}
	cout << "\n";
	return 0;
}
