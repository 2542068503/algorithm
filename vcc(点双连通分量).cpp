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
		if (dfn[v])
		{
			low[u] = min(low[u], dfn[v]);
		}
		else
		{
			child++;
			tarjan(v, u);
			low[u] = min(low[u], low[v]);
			if (low[v] >= dfn[u])
			{
				bcc_cnt++;
				bcc_node[bcc_cnt].pb(u);
				while (!stk.empty())
				{
					ll cur = stk.top();
					stk.pop();
					bcc_node[bcc_cnt].pb(cur);
					if (cur == v)
					{
						break;
					}
				}
			}
		}
	}
	if (f == 0 && child == 0)
	{
		bcc_node[++bcc_cnt].pb(u);
	}
}
