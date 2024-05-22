#include<bits/stdc++.h>
#define ll long long
#define MAX_N 20010
#define MAX_M 100010
using namespace std;
struct edge
{
	int v,next;
}e[MAX_M<<1];
int eid,p[MAX_N];
void insert(int u,int v)
{
	e[++eid].v=v;
	e[eid].next=p[u];
	p[u]=eid;
}
int n;
namespace TARJAN
{
	int idx,dfn[MAX_N],low[MAX_N];//low[]:通过非树边连接到的点的最小dfn
	vector<int>cut;
	void tarjan(int u,int f)
	{
		int son=0;
		dfn[u]=low[u]=++idx;
		for(int i=p[u];i;i=e[i].next)
		{
			int v=e[i].v;
			if(!dfn[v])
			{
				son++;
				tarjan(v,u);
				low[u]=min(low[u],low[v]);
				if(low[v]>=dfn[u]&&u!=f)cut.push_back(u);
			}
			else if(v!=f)//这个判断在求割点的时候加不加都可以，但求割边必须加
                low[u]=min(low[u],dfn[v]);
		}
		if(u==f&&son>=2)cut.push_back(u);
	}
	void calans()
	{
	    for(int i=1;i<=n;++i)
            if(!dfn[i])tarjan(i,i);
        sort(cut.begin(),cut.end());
        vector<int>a;
        if(cut.size())a.push_back(cut[0]);
        for(int i=1;i<cut.size();++i)
            if(cut[i]!=cut[i-1])
                a.push_back(cut[i]);
        cut=a;
        cout<<cut.size()<<endl;
        for(int i=0;i<cut.size();++i)
            cout<<cut[i]<<" ";cout<<endl;
	}
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    int m;cin>>n>>m;
	for(int i=1;i<=m;++i)
	{
		int u,v;
		cin>>u>>v;
		insert(u,v);
		insert(v,u);
	}
	TARJAN::calans();
	return 0;
}
