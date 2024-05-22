#include<bits/stdc++.h>
#define ll long long
#define mid ((l+r)>>1)
#define MOD 998244353
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
ll interpolation(vector<ll>x,vector<ll>y,ll k)
{
	ll ans=0;
	for(int i=0;i<x.size();++i)
	{
		ll sum=y[i];
		for(int j=0;j<x.size();++j)
		{
			if(j==i)continue;
			sum=sum*(k-x[j])%MOD*power(x[i]-x[j])%MOD;
		}
		ans=(ans+sum)%MOD;
	}
	return (ans+MOD)%MOD;
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    ll n,k;cin>>n>>k;
    vector<ll>x(n),y(n);
    for(int i=0;i<n;++i)cin>>x[i]>>y[i];
    cout<<interpolation(x,y,k)<<endl;
	return 0;
}

