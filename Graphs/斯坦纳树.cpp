#include<bits/stdc++.h>
#define ll long long
#define mid ((l+r)>>1)
#define inf 1000000000
#define MAX_M 510
#define MAX_N 110
using namespace std;
struct edge
{
    int v,w,next;
}e[MAX_M<<1];
int eid,p[MAX_N];
void insert(int u,int v,int w)
{
    e[++eid].v=v;
    e[eid].w=w;
    e[eid].next=p[u];
    p[u]=eid;
}
int n;
namespace DIJ
{
    struct node
    {
        int n,d;
        bool operator<(const node&x)const
        {
            return d>x.d;//��Ϊpriority queue�Ǵ�������Է���Ҫ������
        }
    };
    priority_queue<node>q;
    int dis[MAX_N];
    void dijkstra()
    {
        for(int i=1;i<=n;++i)dis[i]=-1;
        while(!q.empty())
        {
            //��ʱ�Ѿ���u�����S���ˣ�u���disֵ�����ٱ�����
            node u=q.top();
            q.pop();

            //����������ɾ��֮ǰ��u������еķ���С���ɳڲ���
            if(dis[u.n]!=-1)continue;//���֮ǰ���ʹ���dis����vis���飩
            dis[u.n]=u.d;
            for(int i=p[u.n];i;i=e[i].next)
            {
                int v=e[i].v;
                if(dis[v]==-1)
                    q.push((node){v,dis[u.n]+e[i].w});//��ʱ������dis���ڶ�������С��dis[u.n]+e[i].w������
            }
        }
    }
}
int dp[MAX_N][1<<11];
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    int m,k;
	cin>>n>>m>>k;
	while(m--)
	{
		int u,v,w;
		cin>>u>>v>>w;
		insert(u,v,w);
		insert(v,u,w);
	}
	for(int s=1;s<(1<<k);++s)
		for(int i=1;i<=n;++i)
			dp[i][s]=inf;
	for(int i=0,key;i<k;++i)cin>>key,dp[key][1<<i]=0;
	
	int ans=inf;
	for(int s=1;s<(1<<k);++s)
	{
		for(int i=1;i<=n;++i)
		{
			for(int sub=(s-1)&s;sub;sub=(sub-1)&s)
				dp[i][s]=min(dp[i][s],dp[i][sub]+dp[i][s^sub]);
			if(dp[i][s]!=inf)DIJ::q.push({i,dp[i][s]});
		}
		DIJ::dijkstra();
		for(int i=1;i<=n;++i)
		{
			dp[i][s]=min(dp[i][s],DIJ::dis[i]==-1?inf:DIJ::dis[i]);
			if(s==(1<<k)-1)ans=min(ans,dp[i][s]);
		}
	}
	cout<<ans<<endl;
	return 0;
}
