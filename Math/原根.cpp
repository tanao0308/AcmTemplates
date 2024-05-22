#include<bits/stdc++.h>
#define ll long long
#define mid ((l+r)>>1)
using namespace std;
ll power(ll a,ll b,ll MOD)
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
vector<ll>primordial_root(ll n)
{
	vector<ll>p;
	ll phi=n,nn=n;
	for(ll i=2;i*i<=nn;++i)
	{
		if(nn%i)continue;
		p.push_back(i);
		while(nn%i==0)nn/=i;
	}
	if(nn!=1)p.push_back(nn);
	if(!(n==2||n==4||(p.size()==1&&p[0]!=2)||(p.size()==2&&p[0]==2&&n%4)))return vector<ll>(0);
	for(ll i=0;i<p.size();++i)phi=phi/p[i]*(p[i]-1);
	
	ll pphi=phi;p.clear();
	for(ll i=2;i*i<=pphi;++i)
	{
		if(pphi%i)continue;
		p.push_back(i);
		while(pphi%i==0)pphi/=i;
	}
	if(pphi>1)p.push_back(pphi);
	vector<ll>ans;
	for(ll i=1;i<=n;++i)
	{
		if(__gcd(i,n)!=1)continue;
		bool flag=0;
		for(ll j=0;j<p.size();++j)
			if(power(i,phi/p[j],n)==1)
				flag=1;
		if(!flag)
		{
			ans.push_back(i);
			break;
		}
	}
	for(ll i=2;i<phi;++i)
		if(__gcd(i,phi)==1)ans.push_back(power(ans[0],i,n));
	return ans;
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    ll T;cin>>T;
    while(T--)
    {
    	ll n,d;
    	cin>>n>>d;
    	vector<ll>ans=primordial_root(n);
    	sort(ans.begin(),ans.end());
    	cout<<ans.size()<<endl;
    	for(ll i=1;i*d-1<ans.size();++i)
    		cout<<ans[i*d-1]<<" ";cout<<endl;
	}
	return 0;
}
