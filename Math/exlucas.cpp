#include<bits/stdc++.h>
#define MAX_N 100010
#define ll long long
#define mid ((l+r)>>1)
using namespace std;
ll power(ll a,ll b,ll p)
{
	ll ans=1;
	while(b)
	{
		if(b&1)ans=ans*a%p;
		a=a*a%p;
		b>>=1;
	}
	return ans;
}
ll exgcd(ll a,ll b,ll&k1,ll&k2)
{
    if(a==0)
    {
        k1=0,k2=1;
        return b;
    }
    ll gcd=exgcd(b%a,a,k1,k2);
    ll kk1=k1,kk2=k2;
    k2=kk1;
    k1=kk2-k2*(b/a);
    return gcd;
}
ll inv(ll n,ll p)
{//所有的逆元都应该用exgcd求，因为不保证模数是质数 
	ll k1,k2;
	exgcd(n,p,k1,k2);
	return k1;
}
namespace LUC
{
	ll crt(vector<ll>a,vector<ll>p)
	{
		ll n=1,ans=0;
		for(ll i=0;i<a.size();++i)n*=p[i];
		for(ll i=0;i<a.size();++i)
		{
			ll m=n/p[i],_m=inv(m,p[i]);//m*_m=1(mod p[i]) -> _m*m+k*p[i]=1 mod(p[i])
			ans=(ans+m*_m%n*a[i]%n)%n;
		}
		return (ans%n+n)%n;
	}
	ll calc(ll n,ll p,ll P)
	{//计算n!/p^x mod P的值 
		if(!n)return 1;
		ll s=1;
		for(ll i=1;i<=P;++i)
			if(i%p)s=s*i%p;
		s=power(s,n/P,P);
		for(ll i=n/P*P+1;i<=n;++i)
			if(i%p)s=(i%P)*s%P;
		return calc(n/p,p,P)*s%P;
	}
	ll multilucas(ll n,ll m,ll p,ll P)//C(n,m) mod (p^x=P)
	{
		ll cnt=0;
		for(ll i=n;i;i/=p)cnt+=i/p;
		for(ll i=m;i;i/=p)cnt-=i/p;
		for(ll i=n-m;i;i/=p)cnt-=i/p;
		//cnt=x-y-z
		return power(p,cnt,P)*calc(n,p,P)%P*inv(calc(m,p,P),P)%P*inv(calc(n-m,p,P),P)%P;
	}
	ll exlucas(ll n,ll m,ll P)
	{
		vector<ll>crtp,crta;
		for(ll p=2;p*p<=P;++p)
		{
			if(P%p)continue;
			crtp.push_back(1);
			while(P%p==0)
				crtp.back()*=p,P/=p;
			crta.push_back(multilucas(n,m,p,crtp.back()));
		}
		if(P>1)crtp.push_back(P),crta.push_back(multilucas(n,m,P,P));
		return crt(crta,crtp);
	}
}
int main()
{
	ll n,m,p;
	cin>>n>>m>>p;
	cout<<LUC::exlucas(n,m,p)<<endl;
	return 0;
}
