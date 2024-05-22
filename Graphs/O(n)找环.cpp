//找一个包含s点的环（最小环）
vector<pair<int,int> >find_circle(int s)
{
	vector<int>vis(n+1,0),fa(n+1,0),pre(n+1,0);
	vector<pair<int,int> >ans;
	for(int i=1;i<=n;++i)vis[i]=pre[i]=fa[i]=0;
	queue<int>q;vis[s]=1;
	for(int i=p[s];i;i=e[i].next)
	{
		int v=e[i].v;
		q.push(v);
		fa[v]=v;pre[v]=s;vis[v]=1;
	}
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(int i=p[u];i;i=e[i].next)
		{
			int v=e[i].v;
			if(vis[v])
			{
				if(v==s||fa[u]==fa[v])continue;
				ans.clear();
				ans.push_back({u,v});
				while(pre[u])ans.push_back({pre[u],u}),u=pre[u];
				while(pre[v])ans.push_back({pre[v],v}),v=pre[v];
				return ans;
			}
			else vis[v]=1,pre[v]=u,fa[v]=fa[u],q.push(v);
		}
	}
	return ans;
}
