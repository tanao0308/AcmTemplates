//https://www.luogu.com.cn/problem/P3403
#include<bits/stdc++.h>
#define ll long long
#define mid ((l+r)>>1)
#define MAX_N 100010
#define MAX_M 200010
#define inf 1e18
using namespace std;
struct edge
{
    ll v,w,next;
}e[MAX_M];
ll eid,p[MAX_N];
void insert(ll u,ll v,ll w)
{
//    cout<<u<<" "<<v<<" "<<w<<endl;
    e[++eid].v=v;
    e[eid].w=w;
    e[eid].next=p[u];
    p[u]=eid;
}

ll n;
namespace DIJ
{
    struct node
    {
        ll n,d;
        bool operator<(const node&x)const
        {
            return d>x.d;//因为priority queue是大根堆所以符号要倒过来
        }
    };
    ll dis[MAX_N];
    bool in_S[MAX_N];
    void dijkstra(ll s)
    {
        priority_queue<node>q;
        while(!q.empty())q.pop();
        for(ll i=0;i<n;++i)dis[i]=-1;//
        q.push((node){s,0});
        while(!q.empty())
        {
            //此时已经将u点加入S中了，u点的dis值不会再被更新
            node u=q.top();
            q.pop();

            //这里是懒惰删除之前把u加入队列的非最小的松弛操作
            if(dis[u.n]!=-1)continue;//如果之前访问过（dis用作vis数组）
            dis[u.n]=u.d;
            for(ll i=p[u.n];i;i=e[i].next)
            {
                ll v=e[i].v;
                if(dis[v]==-1)
                    q.push((node){v,dis[u.n]+e[i].w});//暂时不更新dis，在堆里用最小的dis[u.n]+e[i].w来更新
            }
        }
        
    }
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    ll T;T=1;
    while(T--)
    {
        ll h,x,y,z;cin>>h>>x>>y>>z;
        n=x;h--;
        if(x>y)swap(x,y);
        if(x>z)swap(x,z);
        for(int i=0;i<x;++i)
        {
            insert(i,(i+y)%x,y);
            insert(i,(i+z)%x,z);
        }
        DIJ::dijkstra(0);
        ll ans=0;
        for(int i=0;i<x;++i)
            if(DIJ::dis[i]<=h&&DIJ::dis[i]!=-1)ans+=(h-DIJ::dis[i])/x+1;
        cout<<ans<<endl;
    }
    return 0;
}
