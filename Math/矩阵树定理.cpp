#include<bits/stdc++.h>
#define ll long long
#define mid ((l+r)>>1)
#define MOD 1000000007
using namespace std;
ll power(ll a,ll b=MOD-2)
{
	ll ans=1;
	while(b)
	{
		if(b&1)ans=ans*a%MOD;
		a=a*a%MOD;
		b>>=1;
	}
	return ans;
}
namespace MAT
{
    vector<ll>GaussElimination(vector<vector<ll> >a)
    {
    	bool flag=0;
        for(ll i=0;i<a.size();++i)
        {
            ll p=i;
            for(ll j=p+1;j<a.size();++j)
                if(a[j][i]>a[p][i])p=j;
            if(p!=i)swap(a[i],a[p]),flag^=1;
            
            if(!a[i][i])return vector<ll>(0);//多解或无解返回空vector
            
            ll inv=power(a[i][i]);
            for(ll j=0;j<a.size();++j)
                if(j!=i)for(ll k=a[i].size()-1;k>=i;--k)
                    a[j][k]=(a[j][k]-a[j][i]*inv%MOD*a[i][k]%MOD+MOD)%MOD;
        }
        vector<ll>ans;
        for(ll i=0;i<a.size();++i)
			ans.push_back(a[i][i]);
		if(flag)ans[0]=-ans[0];
        return ans;
    }
}
void print(vector<vector<ll> >a)
{
    for(ll i=0;i<a.size();++i)
    {
        for(ll j=0;j<a[i].size();++j)
            cout<<a[i][j]<<" ";
        cout<<endl;
    }
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    ll n,m,t;cin>>n>>m>>t;
    vector<vector<ll> >g(n-1,vector<ll>(n));
    while(m--)
    {
    	ll u,v,w;cin>>u>>v>>w;
    	u-=2,v-=2;
    	if(u==v)continue;
    	if(t==0)
    	{
	    	if(u>v)swap(u,v);
	    	g[v][v]=(g[v][v]+w)%MOD;
			if(u!=-1)g[u][u]=(g[u][u]+w)%MOD,g[u][v]=(g[u][v]-w+MOD)%MOD,g[v][u]=g[u][v];
		}
		else
		{
			if(u!=-1&&v!=-1)g[u][v]=(g[u][v]-w+MOD)%MOD;
			if(v!=-1)g[v][v]=(g[v][v]+w)%MOD;
		}
	}
	vector<ll>ans=MAT::GaussElimination(g);
	ll sum=1;
	for(ll i=0;i<ans.size();++i)sum=sum*ans[i]%MOD;
	if(n>=2&&!ans.size())cout<<0<<endl;
	else cout<<(sum+MOD)%MOD<<endl;
	return 0;
}
