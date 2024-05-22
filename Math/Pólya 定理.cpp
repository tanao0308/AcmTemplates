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
ll phi(ll n)
{
	ll nn=n;
	vector<ll>p;
	for(ll i=2;i*i<=n;++i)
	{
		if(n%i)continue;
		p.push_back(i);
		while(n%i==0)n/=i;
	}
	if(n!=1)p.push_back(n);
	for(ll i=0;i<p.size();++i)
		nn=nn/p[i]*(p[i]-1);
	return nn;
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    ll T;cin>>T;
    while(T--)
    {
    	ll n,ans=0;
    	cin>>n;
    	for(ll i=1;i*i<=n;++i)
    	{
    		if(n%i)continue;
			if(i*i!=n)ans=(ans+phi(n/i)*power(n,i)+phi(i)*power(n,n/i))%MOD;
			else ans=(ans+phi(n/i)*power(n,i))%MOD;
		}
    	cout<<ans*power(n)%MOD<<endl;
	}
	return 0;
}
/*
Burnside:
 看笔记吧，模板没啥用 
*/
