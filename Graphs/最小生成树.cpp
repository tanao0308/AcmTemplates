#include<bits/stdc++.h>
#define ll long long
#define mid ((l+r)>>1)
#define MAX_N 200010
using namespace std;
struct EDGE
{
    int u,v,w;
};vector<EDGE>g;
bool cmp(EDGE a,EDGE b)
{
    return a.w<b.w;
}
int fa[MAX_N];
int find(int u)
{
    if(fa[u]==u)return u;
    return fa[u]=find(fa[u]);
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    int n,m;cin>>n>>m;
    for(int i=1;i<=n;++i)fa[i]=i;
    for(int i=1;i<=m;++i)
    {
        int u,v,w;
        cin>>u>>v>>w;
        g.push_back({u,v,w});
    }
    sort(g.begin(),g.end(),cmp);
    ll ans=0,cnt=0;
    for(int i=0;i<g.size();++i)
        if(find(g[i].u)!=find(g[i].v))
            fa[find(g[i].u)]=find(g[i].v),ans+=g[i].w,cnt++;
    if(cnt==n-1)
        cout<<ans<<endl;
    else cout<<"orz"<<endl;
    return 0;
}
