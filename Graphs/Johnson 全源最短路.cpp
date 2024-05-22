#include<bits/stdc++.h>
#define ll long long
#define mid ((l+r)>>1)
#define MAX_N 3010
#define MAX_M 6010
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

ll n;
namespace BF
{
    ll dis[MAX_N];
    bool Bellman_Ford(ll s)
    {
        for(ll i=1;i<=n;++i)dis[i]=inf;dis[s]=0;
        bool flag;
        for(ll T=1;T<=n;++T)
        {
            flag=0;
            for(ll u=1;u<=n;++u)
            {
                if(dis[u]==inf)continue;
                for(ll i=p[u];i;i=e[i].next)
                {
                    ll v=e[i].v;
                    if(dis[v]>dis[u]+e[i].w)
                        dis[v]=dis[u]+e[i].w,flag=1;
                }
            }
            if(!flag)break;
        }
        return flag;//flag==1:�и���
    }
}
namespace DIJ
{
    struct node
    {
        ll n,d;
        bool operator<(const node&x)const
        {
            return d>x.d;//��Ϊpriority queue�Ǵ�������Է���Ҫ������
        }
    };
    ll dis[MAX_N];
    bool in_S[MAX_N];
    void dijkstra(ll s)
    {
        priority_queue<node>q;
        while(!q.empty())q.pop();
        for(ll i=1;i<=n;++i)dis[i]=-1;
        q.push((node){s,0});
        while(!q.empty())
        {
            //��ʱ�Ѿ���u�����S���ˣ�u���disֵ�����ٱ�����
            node u=q.top();
            q.pop();

            //����������ɾ��֮ǰ��u������еķ���С���ɳڲ���
            if(dis[u.n]!=-1)continue;//���֮ǰ���ʹ���dis����vis���飩
            dis[u.n]=u.d;
            for(ll i=p[u.n];i;i=e[i].next)
            {
                ll v=e[i].v;
                if(dis[v]==-1)
                    q.push((node){v,dis[u.n]+e[i].w});//��ʱ������dis���ڶ�������С��dis[u.n]+e[i].w������
            }
        }
    }
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    ll m;cin>>n>>m;
    eid=0;for(ll i=1;i<=n;++i)p[i]=0;
    while(m--)
    {
        ll u,v,w;
        cin>>u>>v>>w;
        insert(u,v,w);
    }
    n++;
    for(int i=1;i<n;++i)
        insert(n,i,0);
    if(BF::Bellman_Ford(n))
    {
        cout<<"-1"<<endl;
        return 0;
    }
    p[n]=0,n--;
    BF::Bellman_Ford(1);
    for(int u=1;u<=n;++u)
        for(int i=p[u];i;i=e[i].next)
            e[i].w-=BF::dis[e[i].v]-BF::dis[u];
    for(int i=1;i<=n;++i)
    {
        ll ans=0;
        DIJ::dijkstra(i);
        for(int j=1;j<=n;++j)
            ans+=(DIJ::dis[j]==-1?1e9:DIJ::dis[j]+BF::dis[j]-BF::dis[i])*j;
        cout<<ans<<endl;
    }
    return 0;
}
