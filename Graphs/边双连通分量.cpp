#include<bits/stdc++.h>
#define ll long long
#define MAX_N 1000010
#define MAX_M 4000010
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
namespace DCC
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
	vector<vector<int> >dcc;
	void tarjan(int u,int g)
	{
		dfn[u]=low[u]=++idx;
		s.push(u);
		for(int i=p[u];i;i=e[i].next)
		{
			int v=e[i].v;
			if(!dfn[v])
			{
				tarjan(v,i);
				low[u]=min(low[u],low[v]);
				if(low[v]>dfn[u])
				{
                    vector<int>a;
                    while(!s.empty()&&s.top()!=v)//这里一定是!=v，因为u下面除了v还有其他的子节点，栈里存在 u x1 x2 ... xt v ...这样的结构
                        a.push_back(s.top()),s.pop();
                    if(!s.empty())a.push_back(v),s.pop();
                    dcc.push_back(a);
                }
			}
			else if(i!=(g^1))//这个是不走回头路，可以处理有重边的情况。如果换成v!=f就不能处理重边了
                low[u]=min(low[u],dfn[v]);
		}
	}
	void solve()
	{
	    for(int i=1;i<=n;++i)
            if(!dfn[i])
            {
                insert(i+n,i);
                insert(i,i+n);
                tarjan(i+n,0);
            }
        cout<<dcc.size()<<endl;
        for(int i=0;i<dcc.size();++i)
        {
            cout<<dcc[i].size()<<" ";
            for(int j=0;j<dcc[i].size();++j)
                cout<<dcc[i][j]<<" ";cout<<endl;
        }
	}
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    int m;cin>>n>>m;
    DCC::eid=1;//记得把eid设为1！！！要用到异或取边
	for(int i=1;i<=m;++i)
	{
		int u,v;
		cin>>u>>v;
		if(u==v)continue;
		DCC::insert(u,v);
		DCC::insert(v,u);
	}
	DCC::solve();
	return 0;
}
