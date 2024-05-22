#include<bits/stdc++.h>
#define inf 1e9
#define MAX_N 5010
#define MAX_M 50010
#define ll long long
using namespace std;
struct edge
{
    int v,c,w,next;
}e[MAX_M<<1];
int eid=1,p[MAX_N];//eid=1
void insert(int u,int v,int c,int w){e[++eid]=(edge){v,c,w,p[u]};p[u]=eid;}
void addedge(int u,int v,int c,int w){insert(u,v,c,w);insert(v,u,0,-w);}
namespace MC
{
	int n,s,t,ret,ans;
    int cur[MAX_N],dis[MAX_N];bool vis[MAX_N];
    bool spfa()
    {
        for(int i=1;i<=n;++i)cur[i]=p[i],dis[i]=inf;
        queue<int>q;q.push(s);dis[s]=0,vis[s]=1;
        while(!q.empty())
        {
            int u=q.front();q.pop();vis[u]=0;
            for(int i=p[u];i;i=e[i].next)
            {
                int v=e[i].v;
                if(e[i].c&&dis[v]>dis[u]+e[i].w)
                {
                	dis[v]=dis[u]+e[i].w;
    	            if(!vis[v])q.push(v),vis[v]=1;
    	        }
            }
        }
        return dis[t]!=inf;
    }
    int dfs(int u,int flow)
    {
        if(u==t)return flow;
        int rem=flow;vis[u]=1;
        for(int i=cur[u];i&&rem;i=e[i].next)
        {
            cur[u]=i;
            int v=e[i].v;
            if(vis[v]||e[i].c==0||dis[v]!=dis[u]+e[i].w)continue;
            int minflow=dfs(v,min(rem,e[i].c));
            rem-=minflow;ret+=minflow*e[i].w;
            e[i].c-=minflow;e[i^1].c+=minflow;
        }
        vis[u]=0;
        return flow-rem;
    }
    int mcmf()
    {
    	ret=ans=0;int x;
        while(spfa())
        	while(x=dfs(s,inf))ans+=x;
        return ans;
    }
    void clear()
    {
        eid=1;for(int i=1;i<=n;++i)p[i]=0;
        ret=ans=0;for(int i=1;i<=n;++i)vis[i]=0;
    }
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
	int m;
    cin>>MC::n>>m>>MC::s>>MC::t;
    while(m--)
    {
        int u,v,c,w;
        cin>>u>>v>>c>>w;
        addedge(u,v,c,w);
    }
	cout<<MC::mcmf();cout<<" "<<MC::ret<<endl;
    return 0;
}