#include<bits/stdc++.h>
#define ll long long
#define mid ((l+r)>>1)
#define MAX_N 110
#define MAX_M 100010
using namespace std;
struct edge
{
    int v,next;
}e[MAX_M];
int eid,p[MAX_N];
void insert(int u,int v)
{
    e[++eid].v=v;
    e[eid].next=p[u];
    p[u]=eid;
}
vector<int>topsort(int n)
{
    queue<int>q;vector<int>top,d(n+1,0);
    for(int u=1;u<=n;++u)
		for(int i=p[u];i;i=e[i].next)
			d[e[i].v]++;
    for(int u=1;u<=n;++u)
        if(!d[u])q.push(u);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        top.push_back(u);
        for(int i=p[u];i;i=e[i].next)
        {
            int v=e[i].v;
            d[v]--;
            if(!d[v])q.push(v);
        }
    }
    return top;
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    int n;cin>>n;
    for(int u=1;u<=n;++u)
    {
        int x;cin>>x;
        while(x)insert(u,x),cin>>x;
    }
    vector<int>top=topsort(n);
    for(int i=0;i<top.size();++i)cout<<top[i]<<" ";
    return 0;
}
