#include<bits/stdc++.h>
#define ll long long
#define mid ((l+r)>>1)
using namespace std;
namespace QR
{
	ll p,ii;//p为模数，ii为单位根 
	struct comp
	{
	    ll x,y;
	    comp(ll xx=0,ll yy=0){x=xx,y=yy;}
	};
	comp operator+(comp a,comp b){return comp(a.x+b.x,a.y+b.y);}
	comp operator-(comp a,comp b){return comp(a.x-b.x,a.y-b.y);}
	comp operator*(comp a,comp b){return comp((a.x*b.x%p+a.y*b.y%p*ii)%p,(a.x*b.y%p+a.y*b.x%p)%p);}
	comp operator%(comp a,ll b){return comp((a.x%b+b)%b,(a.y%b+b)%b);}
	comp power(comp a,ll b)
	{
		comp ans(1,0);
		while(b)
		{
			if(b&1)ans=ans*a%p;
			a=a*a%p;
			b>>=1;
		}
		return ans;
	}
	ll residue(ll n)
	{
		return power(n%p,(p-1)/2).x;//之前这里n没取模一直TLE，也是够阴间的  
	}
	ll cipolla(ll n,ll pp)//求ans^2=n mod p 
	{
		p=pp;n%=p;
		if(residue(n)==p-1)return -1;
		else if(n==0)return 0;
		ll a=rand()%p;
		while(residue(a*a-n)!=p-1)a=rand()%p;
		ii=((a*a-n)%p+p)%p;
		comp b(a,1);
		return power(b,(p+1)/2).x;
	}
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
	srand(time(NULL));
	ll T;cin>>T;
	while(T--)
	{
		ll n,p;cin>>n>>p;
		ll ans=QR::cipolla(n,p);
		if(ans==-1)cout<<"Hola!\n";
		else if(ans==0)cout<<"0\n";
		else cout<<min(ans,p-ans)<<" "<<max(ans,p-ans)<<"\n";
	}
	return 0;
}
