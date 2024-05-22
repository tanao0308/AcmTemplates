#include<bits/stdc++.h>
#define ll long long
#define MAX_N 1000010
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
namespace TH
{
    const ll mask=chrono::steady_clock::now().time_since_epoch().count();
    ll shift(ll x)
    {
        x^=mask;
        x^=x<<13;
        x^=x>>7;
        x^=x<<17;
        x^=mask;
        return x;
    }
    ll gethash(int u,int f)
    {
        ll hsh=1;
        for(int i=p[u];i;i=e[i].next)
        {
            int v=e[i].v;
            if(f==v)continue;
            hsh+=shift(gethash(v,u));
        }
        return hsh;
    }
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n;
    for(int i=1;i<n;++i)
    {
        int u,v;
        cin>>u>>v;
        insert(u,v);
        insert(v,u);
    }
    cout<<TH::gethash(1,1)<<endl;
}
