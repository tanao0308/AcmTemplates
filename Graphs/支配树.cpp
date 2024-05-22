#include<bits/stdc++.h>
#define MAX_N 300010
#define ll long long
#define mid ((l+r)>>1)
using namespace std;
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

int idx,dfn[MAX_N],fa[MAX_N];
bool vis[MAX_N];
void dfs1(int u,int f)//dfs的vis数组记得在前面更新，不然会漏掉根节点
{
    fa[u]=f;
    vis[u]=1;
    dfn[u]=++idx;
    for(int i=p[u];i;i=e[i].next)
    {
        int v=e[i].v;
        if(vis[v])continue;
        dfs1(v,u);
    }
}
int a[MAX_N];
bool cmp(int a,int b)
{
    return dfn[a]>dfn[b];
}


struct node
{
    int f,v;
}uni[MAX_N];
void update(int x)
{
    if(uni[x].f==x)return;
    update(uni[x].f);
    uni[x].v+=uni[uni[x].f].v;
    uni[x].f=uni[uni[x].f].f;
}
void merge(int x,int y)//x,y 都是root结点
{
    uni[y].f=x;
    uni[y].v=uni[x].v=y;
}

int hdom[MAX_N];
int main()
{
    int n,m;
    cin>>n>>m;
    while(m--)
    {
        int u,v;
        cin>>u>>v;
        insert(u,v);
        insert(v+n,u+n);//反向边
    }
    dfs1(1,1);dfn[0]=n+1;
    
    for(int i=1;i<=n;++i)a[i]=i,uni[i]=(node){i,0};
    sort(a+1,a+n+1,cmp);
    for(int k=1;k<=n;++k)
    {
        int u=a[k];
        for(int i=p[u+n];i;i=e[i].next)//访问接入点u的点，求u的半支配点
        {
            int v=e[i].v-n;
            if(dfn[v]<dfn[u])
            {
                if(dfn[hdom[u]]>dfn[v])
                    hdom[u]=v;
            }
            else
            {
                update(v);
                int min_dfn_idx=uni[uni[v].f].v;
                if(dfn[hdom[u]]>dfn[min_dfn_idx])
                    hdom[u]=min_dfn_idx;
            }
        }
        merge(fa[u],u);
    }
//    for(int i=1;i<=n;++i)cout<<hdom[i]<<" ";cout<<endl;
    hdom[1]=1;
    return 0;
}
