#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
const ll INF = 1e18;
mt19937 rnd((unsigned int)chrono::steady_clock::now().time_since_epoch().count());
#define pb push_back

constexpr ll N = 1e5;
constexpr double eps = 1e-9;

struct node
{
	double x, y, t, len;
	bool operator<(const node& cmp)const
	{
		if (fabs(x - cmp.x) > eps)
		{
			return x < cmp.x;
		}
		else
		{
			return y < cmp.y;
		}
	}
	bool operator==(const node& cmp)const
	{
		if (fabs(x - cmp.x) < eps && fabs(y - cmp.y) < eps)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
} p[N + 10];

bool cmp(node a, node b)
{
	if (fabs(a.t - b.t) > eps)
	{
		return a.t < b.t;
	}
	else
	{
		return a.len < b.len;
	}
}

double getdis(double x1, double y1, double x2, double y2)
{
	return sqrt(1.0 * (x1 - x2) * (x1 - x2) + 1.0 * (y1 - y2) * (y1 - y2));
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	ll n;
	cin >> n;
	for (ll i = 1; i <= n; i++)
	{
		cin >> p[i].x >> p[i].y;
	}
	sort(p + 1, p + n + 1);
	n = unique(p + 1, p + n + 1) - (p + 1);
	for (ll i = 2; i <= n; i++)
	{
		double x = 1.0 * (p[i].y - p[1].y) / getdis(p[i].x, p[i].y, p[1].x, p[1].y);
		double y = getdis(p[i].x, p[i].y, p[1].x, p[1].y);
		p[i].t = x;
		p[i].len = y;
	}
	sort(p + 2, p + n + 1, cmp);
	stack<node> sta;
	for (ll i = 1; i <= n; i++)
	{
		while (sta.size() >= 2)
		{
			node p2 = sta.top();
			sta.pop();
			node p1 = sta.top();
			sta.pop();
			double x1 = p2.x - p1.x;
			double y1 = p2.y - p1.y;
			double x2 = p[i].x - p2.x;
			double y2 = p[i].y - p2.y;
			sta.push(p1);
			sta.push(p2);
			if (x1 * y2 - x2 * y1 < eps)
			{
				sta.pop();
			}
			else
			{
				break;
			}
		}
		sta.push(p[i]);
	}
	sta.push(p[1]);
	vector<node> v;
	while (!sta.empty())
	{
		v.pb(sta.top());
		sta.pop();
	}
	double ans = 0;
	for (ll i = 0; i < (ll)v.size() - 1; i++)
	{
		ans += sqrt(1.0 * (v[i].x - v[i + 1].x) * (v[i].x - v[i + 1].x) + 1.0 * (v[i].y - v[i + 1].y) * (v[i].y - v[i + 1].y));
	}
	cout << fixed << setprecision(2) << ans << "\n";
	return 0;
}
