#include<bits/stdc++.h>
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
ll inv(ll a,ll p)//(a,p)=1,求a对p的逆元 
{
	ll k1,k2;
	exgcd(a,p,k1,k2);
	return (k1%p+p)%p;
}
map<int,int>mp;
ll BSGS(ll a,ll b,ll p)//a^x=b mod p
{
	a%=p,b%=p;
	ll q=sqrt(p)+1;
	mp.clear();
	for(ll v=0,t=1;v<q;++v,t=t*a%p)
		mp[b*t%p]=v;
	a=power(a,q,p);
	if(!a)return b==0?1:-1;
	for(ll u=1,t=a;u<=q;++u,t=t*a%p)
		if(mp.find(t)!=mp.end())
			return u*q-mp[t];
	return -1;
}
ll exBSGS(ll a,ll b,ll p)
{
	a%=p,b%=p;
	if(b==1||p==1)return 0;
	ll g=__gcd(a,p),k=0,na=1;
	while(g!=1)
	{
		if(b%g)return -1;
		k++,b/=g,p/=g,na=na*(a/g)%p;
		if(na==b)return k;
		g=__gcd(a,p);
	}
	ll ans=BSGS(a,b*inv(na,p),p);
	if(ans!=-1)return ans+k;
	return -1;
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    ll p,a,b;
	while(cin>>a>>p>>b)
	{
		if(!a)return 0;
	    ll ans=exBSGS(a,b,p);
	    if(ans!=-1)cout<<ans<<endl;
	    else cout<<"No Solution"<<endl;
	}
	return 0;
}
/*
x=u*sqrt(p)-v ->
a^u*sqrt(p)=b*a^v
*/
