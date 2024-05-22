#include<bits/stdc++.h>
#define ll long long
#define MAX_N 100010
#define MAX_M 200010
#define inf 1e18
using namespace std;
struct edge
{
    ll v,w,next;
}e[MAX_M<<1];
ll eid,p[MAX_N];
void insert(ll u,ll v,ll w)
{
    e[++eid].v=v;
    e[eid].w=w;
    e[eid].next=p[u];
    p[u]=eid;
}
namespace DIJ
{
    struct node
    {
        ll n,d;
        bool operator<(const node&x)const{return d>x.d;}
    };
    ll n,dis[MAX_N];
    void dijkstra(ll s)
    {
        priority_queue<node>q;
        for(ll i=1;i<=n;++i)dis[i]=-1;
        q.push((node){s,0});
        while(!q.empty())
        {
            node u=q.top();q.pop();
            if(dis[u.n]!=-1)continue;
            dis[u.n]=u.d;
            for(ll i=p[u.n];i;i=e[i].next)
                if(dis[e[i].v]==-1)
                    q.push((node){e[i].v,dis[u.n]+e[i].w});
        }
    }
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    int n,m,s;cin>>n>>m>>s;
    for(ll i=1;i<=m;++i)
    {
        ll u,v,w;
        cin>>u>>v>>w;
        insert(u,v,w);//模板使用的是有向边
    }
    DIJ::n=n;
    DIJ::dijkstra(s);
    for(ll i=1;i<=n;++i)cout<<DIJ::dis[i]<<" ";cout<<endl;
    return 0;
}
