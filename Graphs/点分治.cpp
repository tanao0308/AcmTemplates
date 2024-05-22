/*
假的点分治
因为所有点分治题都能用写法更简洁的dsu on tree解决所以干脆把它当dsu的板题了
*/
#include<bits/stdc++.h>
#define ll long long
#define mid ((l+r)>>1)
#define MAX_N 10010
#define N 10000000
using namespace std;
struct edge
{
	int v,w,next;
}e[MAX_N<<1];
int eid,p[MAX_N];
void insert(int u,int v,int w)
{
	e[++eid].v=v;
	e[eid].w=w;
	e[eid].next=p[u];
	p[u]=eid;
}
int siz[MAX_N],son[MAX_N],val[MAX_N];
void init(int u,int f)
{
	siz[u]=1;
	for(int i=p[u];i;i=e[i].next)
	{
		int v=e[i].v;
		if(v==f)continue;
		val[v]=val[u]+e[i].w;
		init(v,u);
		siz[u]+=siz[v];
		if(!son[u]||siz[v]>siz[son[u]])
			son[u]=v;
	}
}
vector<int>t,mm;
bool mp[10*N+10],ans[N+10];
void subdfs(int u,int f)
{
	t.push_back(val[u]);
	for(int i=p[u];i;i=e[i].next)
	{
		int v=e[i].v;
		if(v!=f)subdfs(v,u);
	}
}
void clear(int u,int f)
{
	mp[val[u]]=0;
	for(int i=p[u];i;i=e[i].next)
	{
		int v=e[i].v;
		if(v!=f)clear(v,u);
	}
}
vector<int>q;
void dfs(int u,int f)
{
	for(int i=p[u];i;i=e[i].next)
	{
		int v=e[i].v;
		if(v==son[u]||v==f)continue;
		dfs(v,u);clear(v,u);mm.clear();
	}
	if(son[u])dfs(son[u],u);
	for(int i=p[u];i;i=e[i].next)
	{
		int v=e[i].v;
		if(v==son[u]||v==f)continue;
		t.clear();subdfs(v,u);
		for(int a=0;a<t.size();++a)
			for(int b=0;b<q.size();++b)
				if(mp[q[b]+2*val[u]-t[a]])
					ans[q[b]]=1;
		for(int a=0;a<t.size();++a)
			mp[t[a]]=1,mm.push_back(t[a]);
	}
	for(int i=0;i<mm.size();++i)
		if(mm[i]-val[u]<=N)
			ans[mm[i]-val[u]]=1;
	mp[val[u]]=1,mm.push_back(val[u]);
}
int main()
{
 	ios::sync_with_stdio(false);cin.tie(0);
 	int n,m;cin>>n>>m;
 	for(int i=1;i<n;++i)
 	{
 		int u,v,w;
 		cin>>u>>v>>w;
 		insert(u,v,w);
 		insert(v,u,w);
	}
	while(m--)
	{
		int d;
		cin>>d;
		q.push_back(d);
	}
	init(1,1);
	dfs(1,1);ans[0]=1;
	for(int i=0;i<q.size();++i)
	{
		if(ans[q[i]])cout<<"AYE"<<"\n";
		else cout<<"NAY"<<"\n";
	}
	return 0;
}
