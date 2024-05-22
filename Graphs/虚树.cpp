//P2495 [SDOI2011] 消耗战
#include<bits/stdc++.h>
#define ll long long
#define mid ((l+r)>>1)
#define MAX_N 250010
using namespace std;
struct edge
{
    int v,w,next;
}e[MAX_N<<1];
int eid,p[MAX_N];
void insert(int u,int v,int w)
{
    e[++eid].v=v;
    e[eid].w=w;
    e[eid].next=p[u];
    p[u]=eid;
}
int n;
namespace VT
{
    int idx,dfn[MAX_N],fa[MAX_N][20],dep[MAX_N],minv[MAX_N];
    void initdfs(int u,int f)
    {
        dfn[u]=++idx;
        dep[u]=dep[f]+1;
        fa[u][0]=f;
        for(int i=1;i<20;++i)
            fa[u][i]=fa[fa[u][i-1]][i-1];
        for(int i=p[u];i;i=e[i].next)
        {
            int v=e[i].v;
            if(v==f)continue;
            minv[v]=min(e[i].w,minv[u]);
            initdfs(v,u);
        }
    }
    void init()
    {
        for(int i=1;i<=n;++i)minv[i]=1e9;
        initdfs(1,0);
    }
    int cal_lca(int u,int v)
    {
        if(dep[u]<dep[v])swap(u,v);
        for(int i=19;i>=0;--i)
            if(dep[fa[u][i]]>=dep[v])
                u=fa[u][i];
        if(u==v)return u;
        for(int i=19;i>=0;--i)
            if(fa[u][i]!=fa[v][i])
                u=fa[u][i],v=fa[v][i];
        return fa[u][0];
    }
    struct node
    {
        int v,n;
    };
    bool cmp(node a,node b)
    {
        return a.v<b.v;
    }

    bool imp[MAX_N];
    edge e2[MAX_N<<2];
    int eid2,p2[MAX_N];
    void insert2(int u,int v,int w)
    {
        e2[++eid2].v=v;
        e2[eid2].w=w;
        e2[eid2].next=p2[u];
        p2[u]=eid2;
    }
    int build(vector<int>dot)
    {
        //接下来是构建虚树的板子
        eid2=0;//清空虚树边
        vector<node>a;
        for(int i=0;i<dot.size();++i)
            a.push_back((node){dfn[dot[i]],dot[i]}),imp[dot[i]]=1;
        //以dfn为关键词排序，所以a[i].v=dfn[a[i].n]
        sort(a.begin(),a.end(),cmp);
        stack<int>s;
        while(!s.empty())s.pop();s.push(0),s.push(a[0].n);
        for(int i=1;i<a.size();++i)
        {
            int u=a[i].n;
            int lca=cal_lca(s.top(),u);
            while(1)
            {
                int uu=s.top();s.pop();int ff=s.top();s.push(uu);
                if(dep[lca]>=dep[ff])
                {
                    if(lca!=uu)
                    {
                        insert2(lca,uu,0),insert2(uu,lca,0);
                        if(lca!=ff)s.top()=lca;
                        else s.pop();
                    }
                    break;
                }
                else insert2(uu,ff,0),insert2(ff,uu,0),s.pop();
            }
            s.push(u);
        }
        while(s.size()>=3)
        {
            int uu=s.top();s.pop();int ff=s.top();s.push(uu);
            insert2(uu,ff,0),insert2(ff,uu,0);
            s.pop();
        }
        return s.top();
    }
    
    ll dfs(int u,int f)
    {
        ll sum=0,ans=0;
        for(int i=p2[u];i;i=e2[i].next)
        {
            int v=e2[i].v;
            if(v==f)continue;
            sum+=dfs(v,u);
        }
        if(imp[u])ans=minv[u];
        else ans=min((ll)minv[u],sum);
        p2[u]=imp[u]=0;
        return ans;
    }
    void calans(vector<int>dot)
    {
        int rt=build(dot);
        cout<<dfs(rt,rt)<<endl;
    }
}
int main()
{
    cin>>n;
    for(int i=1;i<n;++i)
    {
        int u,v,w;
        cin>>u>>v>>w;
        insert(u,v,w),insert(v,u,w);
    }
    VT::init();
    int m;cin>>m;
    while(m--)
    {
        int k;cin>>k;
        vector<int>dot;
        for(int i=0,x;i<k;++i)
            cin>>x,dot.push_back(x);
        VT::calans(dot);
    }
    return 0;
}
