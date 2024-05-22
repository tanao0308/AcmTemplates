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
namespace FWT
{
	vector<ll>fwt_or(vector<ll>a,ll on)
	{
		for(int n=2;n<=a.size();n<<=1)
			for(int j=0;j<a.size();j+=n)
				for(int k=j;k<j+n/2;++k)
					a[k+n/2]=(a[k+n/2]+on*a[k]+MOD)%MOD;
		return a;
	}
	vector<ll>OR(vector<ll>a,vector<ll>b)
	{
	    a=fwt_or(a,1),b=fwt_or(b,1);
	    vector<ll>c;
	    for(int i=0;i<a.size();++i)c.push_back(a[i]*b[i]%MOD);
	    return fwt_or(c,-1);
	}
	vector<ll>fwt_and(vector<ll>a,ll on)
	{
		for(int n=2;n<=a.size();n<<=1)
			for(int j=0;j<a.size();j+=n)
				for(int k=j;k<j+n/2;++k)
					a[k]=(a[k]+on*a[k+n/2]+MOD)%MOD;
		return a;
	}
	vector<ll>AND(vector<ll>a,vector<ll>b)
	{
	    a=fwt_and(a,1),b=fwt_and(b,1);
	    vector<ll>c;
	    for(int i=0;i<a.size();++i)c.push_back(a[i]*b[i]%MOD);
	    return fwt_and(c,-1);
	}
	vector<ll>fwt_xor(vector<ll>a,ll on)
	{
		for(int n=2;n<=a.size();n<<=1)
			for(int j=0;j<a.size();j+=n)
				for(int k=j;k<j+n/2;++k)
				{
					a[k]=(a[k]+a[k+n/2])%MOD;
					a[k+n/2]=(a[k]-2*a[k+n/2]+2*MOD)%MOD;
					a[k]=(on*a[k])%MOD,a[k+n/2]=(on*a[k+n/2])%MOD;
				}
		return a;
	}
	vector<ll>XOR(vector<ll>a,vector<ll>b)
	{
	    a=fwt_xor(a,1),b=fwt_xor(b,1);
	    vector<ll>c;
	    for(int i=0;i<a.size();++i)c.push_back(a[i]*b[i]%MOD);
	    return fwt_xor(c,power(2));
	}
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    ll n;cin>>n;n=(1<<n);
    vector<ll>a,b,c;ll x;
    for(int i=1;i<=n;++i)cin>>x,a.push_back(x);
    for(int i=1;i<=n;++i)cin>>x,b.push_back(x);
    c=FWT::OR(a,b);
    for(int i=0;i<n;++i)cout<<c[i]<<" ";cout<<endl;
    c=FWT::AND(a,b);
    for(int i=0;i<n;++i)cout<<c[i]<<" ";cout<<endl;
    c=FWT::XOR(a,b);
    for(int i=0;i<n;++i)cout<<c[i]<<" ";cout<<endl;
	return 0;
}

