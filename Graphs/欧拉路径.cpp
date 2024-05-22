#include<bits/stdc++.h>
#define mid ((l+r)>>1)
#define MAX_N 100010
#define MAX_M 200010
using namespace std;
typedef long long ll;
struct edge
{
    int v,next;
}e[MAX_M];
int eid,p[MAX_N];
void insert(int u,int v)
{
    e[++eid].v=v;
    e[eid].next=p[u];
    p[u]=eid;
}
vector<int>g[MAX_N];
int d[MAX_N],cur[MAX_N];
stack<int>s;
void dfs(int u)
{
	while(cur[u]<g[u].size())
		dfs(g[u][cur[u]++]);
	s.push(u);
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    int n,m;cin>>n>>m;
    while(m--)
    {
    	int u,v;cin>>u>>v;
    	g[u].push_back(v);
    	d[u]++,d[v]--;
    }
    int cnt=0;
    for(int i=1;i<=n;++i)
    	if(d[i]==1||d[i]==-1)++cnt;
    	else if(d[i]!=0)
    	{
    		cout<<"No"<<endl;
    		return 0;
    	}
    if(cnt>2)
    {
    	cout<<"No"<<endl;
    	return 0;
    }
    for(int u=1;u<=n;++u)sort(g[u].begin(),g[u].end());
    for(int i=1;i<=n;++i)
    	if(d[i]==1)dfs(i);
    if(!cnt)dfs(1);
    while(!s.empty())cout<<s.top()<<" ",s.pop();
    cout<<endl;
    return 0;
}