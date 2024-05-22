// tarjan 缩点后，所属连通块编号越小，节点越靠近叶子节点这一性质
#include<bits/stdc++.h>
#define ll long long
#define MAX_N 10010
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
namespace SCC
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
    bool in[MAX_N];
    int idx,dfn[MAX_N],low[MAX_N];
    stack<int>s;
    vector<vector<int> >scc;
    void tarjan(int u)
    {
        in[u]=1;
        dfn[u]=low[u]=++idx;
        s.push(u);
        for(int i=p[u];i;i=e[i].next)
        {
            int v=e[i].v;
            if(!dfn[v])tarjan(v),low[u]=min(low[u],low[v]);
            if(in[v])low[u]=min(low[u],low[v]);
            //else 横叉边，不处理
        }
        if(dfn[u]==low[u])//强联通分量根节点
        {
            vector<int>a;
            while(s.top()!=u)
                in[s.top()]=0,a.push_back(s.top()),s.pop();
            in[u]=0,a.push_back(u),s.pop();
            scc.push_back(a);
        }
    }
    void solve()
    {
        for(int i=1;i<=n;++i)
            if(!dfn[i])tarjan(i);
    }
}
bool cmp(vector<int>a,vector<int>b)
{
    return a[0]<b[0];
}
int main()
{
    int m;cin>>n>>m;
    while(m--)
    {
        int u,v;
        cin>>u>>v;
        SCC::insert(u,v);
    }
    SCC::solve();
    for(int i=0;i<SCC::scc.size();++i)
        sort(SCC::scc[i].begin(),SCC::scc[i].end());
    sort(SCC::scc.begin(),SCC::scc.end(),cmp);
    cout<<SCC::scc.size()<<endl;
    for(int i=0;i<SCC::scc.size();++i)
    {
        for(int j=0;j<SCC::scc[i].size();++j)
            cout<<SCC::scc[i][j]<<" ";
        cout<<endl;
    }
    return 0;
}
