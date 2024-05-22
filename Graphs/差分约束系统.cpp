#include<bits/stdc++.h>
#define ll long long
#define mid ((l+r)>>1)
#define MAX_N 5010
#define MAX_M 5010
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

vector<int>dd;
bool spfa(int n)
{
    queue<int>q;
    vector<int>dis(n+1,1e9),vis(n+1,0),cnt(n+1,0);
    for(int i=1;i<=n;++i)
        dis[i]=0,vis[i]=1,q.push(i);
    while(!q.empty())
    {
        int u=q.front();q.pop();vis[u]=0;
        for(int i=p[u];i;i=e[i].next)
        {
            int v=e[i].v,w=e[i].w;
            if(dis[u]+w<dis[v])
            {
                dis[v]=dis[u]+w;
                if(!vis[v])
                {
                    if(++cnt[v]>=n)return 1;
                    vis[v]=1;q.push(v);
                }
            }
        }
    }
    dd=dis;
    return 0;
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    ll T;T=1;
    while(T--)
    {
        ll n,m;cin>>n>>m;
        eid=0;for(ll i=1;i<=n;++i)p[i]=0;
        while(m--)
        {
            ll u,v,w;
            cin>>u>>v>>w;
            insert(v,u,w);
        }
        n++;for(int i=1;i<n;++i)insert(n,i,0);
        if(spfa(n))cout<<"NO"<<endl;
        else
        {
            for(int i=1;i<n;++i)
                cout<<dd[i]<<" ";cout<<endl;
        }
    }
    return 0;
}
