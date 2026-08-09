struct mtx
{
	ull mat[65][65];
	mtx()
	{
		memset(mat, 0, sizeof(mat));
	}
	void init()
	{
		for (ll i = 0; i < 65; i++)
		{
			mat[i][i] = 1;
		}
	}
	mtx operator * (const mtx& oth)const
	{
		mtx c;
		for (ll i = 0; i < 65; i++)
		{
			for (ll k = 0; k < 65; k++)
			{
				if (!mat[i][k])
				{
					continue;
				}
				for (ll j = 0; j < 65; j++)
				{
					c.mat[i][j] += mat[i][k] * oth.mat[k][j];
				}
			}
		}
		return c;
	}
};

mtx mtxpow(mtx a, ll b)
{
	mtx res;
	res.init();
	while (b)
	{
		if (b & 1)
		{
			res = res * a;
		}
		a = a * a;
		b >>= 1;
	}
	return res;
}
