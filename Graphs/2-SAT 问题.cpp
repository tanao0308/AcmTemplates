#include<bits/stdc++.h>
#define ll long long
#define MAX_N 2000010
#define MAX_M 1000010
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
namespace TAR
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
                s.pop();
            }
            in[u]=0,scc[u]=col,s.pop();
        }
    }
    int val[MAX_N];
    void calans()
    {
        n<<=1;
        for(int i=1;i<=n;++i)
            if(!dfn[i])tarjan(i);
        //tarjan求出的强连通分量是逆拓扑序存放的
        
        n>>=1;
        for(int i=1;i<=n;++i)
        {
            int sc=scc[i];//xi 对应的强连通分量
            int _sc=scc[i+n];//!xi 对应的强连通分量
            if(sc==_sc)
            {
                cout<<"IMPOSSIBLE"<<endl;
                return;
            }
            val[min(sc,_sc)]=1,val[max(sc,_sc)]=0;
        }
        cout<<"POSSIBLE"<<endl;
        for(int i=1;i<=n;++i)
            cout<<val[scc[i]]<<" ";cout<<endl;
    }
}
int main()
{
    int m;cin>>n>>m;
    while(m--)
    {
        int u,v,a,b;
        cin>>u>>a>>v>>b;
        u+=(1-a)*n,v+=(1-b)*n;//xi:1-n !xi:n+1-2*n
        insert((u+n)%(2*n),v);
        insert((v+n)%(2*n),u);
    }
    TAR::calans();
    return 0;
}
