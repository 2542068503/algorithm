ll exgcd(ll a, ll b, ll &x, ll &y)
{
	if (!b)
	{
		x = 1, y = 0;
		return a;
	}
	ll d = exgcd(b, a % b, y, x); // 注意是先传 y 再传 x  
	y -= (a / b) * x;
	return d;
}
