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
int n,val[MAX_N];
namespace SCC
{
    bool in[MAX_N];
    int idx,col,scc[MAX_N],dfn[MAX_N],low[MAX_N];
    stack<int>s;
    void tarjan(int u)
    {
        in[u]=1;
        dfn[u]=low[u]=++idx;
        s.push(u);
        for(int i=p[u];i;i=e[i].next)
        {
            int v=e[i].v;
            if(!dfn[v])
                tarjan(v),low[u]=min(low[u],low[v]);
            if(in[v])
                low[u]=min(low[u],low[v]);
            //else 横叉边，不处理
        }
        if(dfn[u]==low[u])//强联通分量根节点
        {
            ++col;
            while(s.top()!=u)
            {
                in[s.top()]=0;
                scc[s.top()]=col;
                val[col+n]+=val[s.top()];
                s.pop();
            }
            in[u]=0,scc[u]=col,val[col+n]+=val[u],s.pop();
        }
    }
    int d[MAX_N<<1],dp[MAX_N<<1];
    vector<int>topsort()
    {
        queue<int>q;vector<int>top;
        for(int u=n+1;u<=n+col;++u)
            if(!d[u])q.push(u);
        while(!q.empty())
        {
            int u=q.front();q.pop();
            top.push_back(u);
            for(int i=p[u];i;i=e[i].next)
            {
                int v=e[i].v;
                d[v]--;
                if(!d[v])q.push(v);
            }
        }
        return top;
    }
    void calans()
    {
        for(int i=1;i<=n;++i)
            if(!dfn[i])tarjan(i);
        for(int u=1;u<=n;++u)
            for(int i=p[u];i;i=e[i].next)
            {
                int v=e[i].v;
                if(scc[u]!=scc[v])insert(scc[u]+n,scc[v]+n),d[scc[v]+n]++;
            }
        int ans=0;
        vector<int>top=topsort();
        for(int k=top.size()-1;k>=0;--k)
        {
            int u=top[k];
            dp[u]=val[u];
            for(int i=p[u];i;i=e[i].next)
            {
                int v=e[i].v;
                dp[u]=max(dp[u],dp[v]+val[u]);
            }
            ans=max(ans,dp[u]);
        }
        cout<<ans<<endl;
    }
}
int main()
{
    int m;cin>>n>>m;
    for(int i=1;i<=n;++i)cin>>val[i];
    while(m--)
    {
        int u,v;
        cin>>u>>v;
        insert(u,v);
    }
    SCC::calans();
    return 0;
}
