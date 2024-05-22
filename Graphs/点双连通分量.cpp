#include<bits/stdc++.h>
#define ll long long
#define MAX_N 500010
#define MAX_M 2000010
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
namespace BCC
{
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
	int idx,dfn[MAX_N],low[MAX_N];
    stack<int>s;
	vector<vector<int> >bcc;
	void tarjan(int u,int f)
	{
		int son=0;
		dfn[u]=low[u]=++idx;
		s.push(u);
		for(int i=p[u];i;i=e[i].next)
		{
			int v=e[i].v;
			if(!dfn[v])
			{
				son++;
				tarjan(v,u);
				low[u]=min(low[u],low[v]);
				if(low[v]>=dfn[u])
				{
                    vector<int>a;
                    while(!s.empty()&&s.top()!=v)//这里一定是!=v，因为u下面除了v还有其他的子节点，栈里存在 u x1 x2 ... xt v ...这样的结构
                        a.push_back(s.top()),s.pop();
                    if(!s.empty())a.push_back(v),s.pop();
                    a.push_back(u);
                    bcc.push_back(a);
                }
			}
			else if(v!=f)//这个判断在求割点的时候加不加都可以，但求割边必须加
                low[u]=min(low[u],dfn[v]);
		}
		if(u==f&&son==0)bcc.push_back({u});
	}
	void solve()
	{
	    for(int i=1;i<=n;++i)
            if(!dfn[i])tarjan(i,i);
        cout<<bcc.size()<<endl;
        for(int i=0;i<bcc.size();++i)
        {
            cout<<bcc[i].size()<<" ";
            for(int j=0;j<bcc[i].size();++j)
                cout<<bcc[i][j]<<" ";cout<<endl;
        }
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
		BCC::insert(u,v);
		BCC::insert(v,u);
	}
	BCC::solve();
	return 0;
}
