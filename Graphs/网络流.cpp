#include<bits/stdc++.h>
#define inf 1e9
#define MAX_N 210
#define MAX_M 5010
#define ll long long
using namespace std;
struct edge
{
    ll v,w,next;
}e[MAX_M<<1];
ll eid=1,p[MAX_N];
void insert(ll u,ll v,ll w){e[++eid]=(edge){v,w,p[u]};p[u]=eid;}
void addedge(int u,int v,int w){insert(u,v,w),insert(v,u,0);}
namespace FL
{
	ll n,s,t;
    ll lv[MAX_N],cur[MAX_N];
    bool bfs()
    {
        for(ll i=1;i<=n;++i)cur[i]=p[i];
        queue<ll>q;q.push(s);
        memset(lv,-1,sizeof lv);lv[s]=0;
        while(!q.empty())
        {
            ll u=q.front();
            q.pop();
            for(ll i=p[u];i;i=e[i].next)
            {
                ll v=e[i].v;
                if(lv[v]!=-1||e[i].w==0)continue;
                lv[v]=lv[u]+1;
                q.push(v);
            }
        }
        return lv[t]!=-1;
    }
    ll dfs(ll u,ll FL)
    {
        if(u==t)return FL;
        ll rem=FL;
        for(ll i=cur[u];i&&rem;i=e[i].next)
        {
            cur[u]=i;
            ll v=e[i].v;
            if(lv[v]<=lv[u]||e[i].w==0)continue;
            ll minFL=dfs(v,min(rem,e[i].w));
            rem-=minFL;e[i].w-=minFL;e[i^1].w+=minFL;
        }
        return FL-rem;
    }
    int dinic()
    {
        ll ans=0;
        while(bfs())ans+=dfs(s,inf);
        return ans;
    }
    void clear(){eid=1;for(int i=1;i<=n;++i)p[i]=0;}
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
	int n,m,s,t;cin>>n>>m>>s>>t;
    for(ll i=1;i<=m;++i)
    {
        ll u,v,w;
        cin>>u>>v>>w;
        insert(u,v,w);
        insert(v,u,0);
    }
    FL::n=n,FL::s=s,FL::t=t;
    cout<<FL::dinic()<<endl;
    FL::clear();
    return 0;
}
