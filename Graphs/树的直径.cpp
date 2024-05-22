#include<bits/stdc++.h>
#define ll long long
#define mid ((l+r)>>1)
#define MAX_N 100010
using namespace std;
struct edge
{
    int v,next;
}e[MAX_N<<1];
int eid,p[MAX_N];
void insert(int u,int v)
{
    e[++eid].v=v;
    e[eid].next=p[u];
    p[u]=eid;
}
int n;
namespace DIA
{
    int len[MAX_N],fa[MAX_N];
    void dfs(int u,int f)
    {
        len[u]=len[f]+1;
        fa[u]=f;
        for(int i=p[u];i;i=e[i].next)
        {
            int v=e[i].v;
            if(v==f)continue;
            dfs(v,u);
        }
    }
    vector<int>diameter()
    {
        len[0]=-1;
        dfs(1,0);
        int l=1;
        for(int i=1;i<=n;++i)if(len[l]<len[i])l=i;
        dfs(l,0);
        int r=l;
        for(int i=1;i<=n;++i)if(len[r]<len[i])r=i;
        int p=r;vector<int>dia;
        while(p)dia.push_back(p),p=fa[p];
        return dia;
    }
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n;
    for(int i=1;i<n;++i)
    {
        int u,v;cin>>u>>v;
        insert(u,v);
        insert(v,u);
    }
    vector<int>dia=DIA::diameter();
    cout<<dia.size()-1<<endl;
    for(int i=0;i<dia.size();++i)cout<<dia[i]<<" ";cout<<endl;
    return 0;
}
