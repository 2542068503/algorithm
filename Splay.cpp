bool dir(ll x)
{
	return ch[fa[x]][1] == x; // 0 为左儿子，1 为右儿子
}

void rotate(ll x)
{
	ll y = fa[x], z = fa[y];
	ll k = dir(x);
	ch[y][k] = ch[x][k ^ 1];
	if (ch[x][k ^ 1]) fa[ch[x][k ^ 1]] = y;
	ch[x][k ^ 1] = y;
	fa[y] = x;
	fa[x] = z;
	if (z) ch[z][dir(y)] = x; // 这里甚至能直接复用 which(y) 替代 ch[z][1] == y
	pushup(y);
	pushup(x);
}

void splay(ll x, ll goal = 0)
{
	while (fa[x] != goal)
	{
		ll p = fa[x];
		ll g = fa[p];
		if (g != goal) // 至少还有两层才能到达目标，需要双旋
		{
			if (get(x) == get(p))
			{
				// 情况 2：一字形 (Zig-Zig)，同向
				// 必须先旋父节点 p！
				rotate(p);
			}
			else
			{
				// 情况 3：之字形 (Zig-Zag)，异向
				// 连续旋自己两次（这里先旋一次 x）
				rotate(x);
			}
		}
		// 无论是哪种情况，最后一步都是旋自己 x
		rotate(x);
	}
	if (!goal) rt = x;
}
