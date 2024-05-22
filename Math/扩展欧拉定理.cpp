#include<bits/stdc++.h>
#define ll long long
#define mid ((l+r)>>1)
using namespace std;
ll phi(ll n)
{
	ll nn=n;
	vector<ll>p;
	for(ll i=2;i*i<=n;++i)
	{
		if(n%i==0)p.push_back(i);
		while(n%i==0)n/=i;
	}
	if(n!=1)p.push_back(n);
	for(ll i=0;i<p.size();++i)nn=nn/p[i]*(p[i]-1);
	return nn;
}
ll power(ll a,ll b,ll m)
{
	ll ans=1;
	while(b)
	{
		if(b&1)ans=ans*a%m;
		a=a*a%m;
		b>>=1;
	}
	return ans;
}
ll exeuler(ll a,string s,ll m)
{
    ll phim=phi(m),b=0;
    bool flag=0;
    for(ll i=s.length()-1,p=1;i>=0;--i,p=p*10)
    {
    	if(b+(s[i]-'0')*p>=phim)flag=1;
    	p%=phim;
    	b=(b+(s[i]-'0')*p)%phim;
    }
    if(flag)b+=phim;
    return power(a,b,m);
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    ll a,m;string s; 
    cin>>a>>m>>s;
    cout<<exeuler(a,s,m)<<endl;
	return 0;
}

