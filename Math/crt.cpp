#include<bits/stdc++.h>
#define ll long long
#define mid ((l+r)>>1)
using namespace std;
ll exgcd(ll a,ll b,ll&x,ll&y)
{
    if(!b)return x=1,y=0,a;
    ll d=exgcd(b,a%b,x,y),t=x;
    return x=y,y=t-a/b*y,d;
}
ll crt(vector<ll>a,vector<ll>p)
{
	ll n=1,ans=0;
	for(int i=0;i<a.size();++i)n*=p[i];
	for(int i=0;i<a.size();++i)
	{
		ll m=n/p[i],_m,k;
		exgcd(m,p[i],_m,k);//m*_m=1(mod p[i]) -> _m*m+k*p[i]=1 mod(p[i])
		ans=(ans+m*_m%n*a[i]%n)%n;
	}
	return (ans%n+n)%n;
}
int main()
{
	int n;cin>>n;
	vector<ll>a(n),p(n);
	for(int i=0;i<n;++i)
		cin>>p[i]>>a[i];
	cout<<crt(a,p)<<endl;
	return 0;
}

