#include<bits/stdc++.h>
#define ll long long
#define mid ((l+r)>>1)
#define MAX_N 140010
#define MAX_M 100010
#define MOD 1000000007
using namespace std;
struct EDGE
{
    int u,v,w;
    bool operator<(const EDGE&x)const
    {
        return w<x.w;
    }
};vector<EDGE>g;
int fa[MAX_N<<1];
int find(int u)
{
    if(fa[u]==u)return u;
    return fa[u]=find(fa[u]);
}
struct edge
{
    int v,next;
}e[MAX_N<<2];
int eid,p[MAX_N<<1];
void insert(int u,int v)
{
    e[++eid].v=v;
    e[eid].next=p[u];
    p[u]=eid;
}
int idx,dfn[MAX_N<<1],lft[MAX_N<<1],dep[MAX_N<<1];
void dfs(int u,int f)
{
    dep[u]=dep[f]+1;
    dfn[++idx]=u;//这里的dfn求法是重中之重！！！
    lft[u]=idx;
    for(int i=p[u];i;i=e[i].next)
    {
        int v=e[i].v;
        if(v==f)continue;
        dfs(v,u);
        dfn[++idx]=u;//还有这里！！！
    }
}

int A,B,C,P;
inline int rnd(){return A=(A*B+C)%P;}
int lg[MAX_N<<1],val[MAX_N];
int lca[MAX_N<<1][20],mindep[MAX_N<<1][20];
int query(int l,int r)
{
    if(!lg[r-l+1])lg[r-l+1]=log(r-l+1)/log(2);
    int x=lg[r-l+1];
    int ans=0;
    if(mindep[l][x]<=mindep[r-(1<<x)+1][x])ans=lca[l][x];
    else ans=lca[r-(1<<x)+1][x];
    return val[ans];
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    int n,m;cin>>n>>m;
    while(m--)
    {
        int u,v,w;
        cin>>u>>v>>w;
        g.push_back((EDGE){u,v,w});
    }
    for(int i=1;i<=2*n;++i)fa[i]=i;
    sort(g.begin(),g.end());
    int cnt=n;
    for(int i=0;i<g.size();++i)
    {
        int u=find(g[i].u),v=find(g[i].v),w=g[i].w;
        if(u==v)continue;
        fa[u]=fa[v]=++cnt;
        val[cnt]=w;
        insert(u,cnt),insert(cnt,u);
        insert(v,cnt),insert(cnt,v);
    }
    dfs(cnt,cnt);
    for(int i=1;i<=idx;++i)
        mindep[i][0]=dep[dfn[i]],lca[i][0]=dfn[i];
    for(int i=1;i<20;++i)
        for(int j=1;j+(1<<i)<=idx;++j)
        {
            if(mindep[j][i-1]<=mindep[j+(1<<(i-1))][i-1])
                mindep[j][i]=mindep[j][i-1],lca[j][i]=lca[j][i-1];
            else mindep[j][i]=mindep[j+(1<<(i-1))][i-1],lca[j][i]=lca[j+(1<<(i-1))][i-1];
        }
    ll q;
    cin>>q>>A>>B>>C>>P;
    ll ans=0;
    while(q--)
    {
        int u=rnd()%n+1,v=rnd()%n+1;
        ans+=query(min(lft[u],lft[v]),max(lft[u],lft[v]));
        ans%=MOD;
    }
    cout<<ans<<endl;
    return 0;
}
