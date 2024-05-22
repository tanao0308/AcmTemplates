#include<bits/stdc++.h>
#define ll long long
#define mid ((l+r)>>1)
#define MAX_N 100010
using namespace std;
struct edge
{
	int v,next;
}e[MAX_N<<1];
int eid,p[MAX_N];
void insert(int u,int v)
{
	e[++eid].v=v;
	e[eid].next=p[u];
	p[u]=eid;
}
int siz[MAX_N],son[MAX_N];
void init(int u,int f)
{
	siz[u]=1;
	for(int i=p[u];i;i=e[i].next)
	{
		int v=e[i].v;
		if(v==f)continue;
		init(v,u);
		siz[u]+=siz[v];
		if(!son[u]||siz[v]>siz[son[u]])
			son[u]=v;
	}
}
#define N 100000
int mp[N+10];
int cnt,ans[MAX_N],col[MAX_N];
void subdfs(int u,int f)
{
	for(int i=p[u];i;i=e[i].next)
	{
		int v=e[i].v;
		if(v!=f)subdfs(v,u);
	}
	if(!mp[col[u]])cnt++;
	mp[col[u]]++;
}
void clear(int u,int f)
{
	mp[col[u]]=0;
	for(int i=p[u];i;i=e[i].next)
	{
		int v=e[i].v;
		if(v!=f)clear(v,u);
	}
}
void dfs(int u,int f)
{
	for(int i=p[u];i;i=e[i].next)
	{
		int v=e[i].v;
		if(v==son[u]||v==f)continue;
		dfs(v,u);clear(v,u),cnt=0;
	}
	if(son[u])dfs(son[u],u);
	if(!mp[col[u]])cnt++;
	mp[col[u]]++;
	for(int i=p[u];i;i=e[i].next)
	{
		int v=e[i].v;
		if(v==son[u]||v==f)continue;
		subdfs(v,u);
	}
	ans[u]=cnt;
}
int main()
{
 	ios::sync_with_stdio(false);cin.tie(0);
 	int n;cin>>n;
 	for(int i=1;i<=N;++i)mp[i]=0;
 	for(int i=1;i<n;++i)
 	{
 		int u,v;
 		cin>>u>>v;
 		insert(u,v);
 		insert(v,u);
	}
	for(int i=1;i<=n;++i)cin>>col[i];
	init(1,1);
	dfs(1,1);
	int q;cin>>q;
	while(q--)
	{
		int u;cin>>u;
		cout<<ans[u]<<"\n";
	}
	return 0;
}
