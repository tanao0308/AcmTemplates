#include<bits/stdc++.h>
#define ll long long
#define LL __int128
#define mid ((l+r)>>1)
using namespace std;
ll power(ll a,ll b,ll p)
{
	ll ans=1;
	while(b)
	{
		if(b&1)ans=(LL)ans*a%p;
		a=(LL)a*a%p;
		b>>=1;
	}
	return ans;
}
namespace PR
{
	bool check_prime(ll n)
	{//Ã×ÀÕÂÞ±ö·¨
		static const int jp[]={2,3,5,7,11,13,17,19,23,29};
		if(n==1)return false;
		for(int p:jp)if(n%p==0)return n==p;
		ll r=n-1,x,y;
		int e=0;
		while(~r&1)r>>=1,++e;
		for(int p:jp)
		{
			x=power(p,r,n);
			for(int t=0;t<e&&x>1;++t)
			{
				y=(LL)x*x%n;
				if(y==1&&x!=n-1)return 0;
				x=y;
			}
			if(x!=1)return 0;
		}
		return 1;
	}
	ll f(ll x,ll c,ll n){return ((LL)x*x+c)%n;}
	inline ll Pollard_Rho(ll x)
	{
	    ll s=0,t=0,c=(ll)rand()%(x-1)+1;
	    int stp=0,goal=1;
	    ll val=1;
	    for(goal=1;;goal<<=1,s=t,val=1)
	    {
	        for(stp=1;stp<=goal;++stp)
	        {
	            t=f(t,c,x);
	            val=(LL)val*abs(t-s)%x;
	            if((stp%127)==0)
	            {
	                ll d=__gcd(val,x);
	                if(d>1)return d;
	            }
	        }
	        ll d=__gcd(val,x);
	        if(d>1)return d;
	    }
	}
	set<ll>prime;
	void fac(ll x)
	{
	    if(x<=1)return;
	    if(check_prime(x))
	    {
	    	prime.insert(x);
	        return;
	    }
	    ll p=x;
	    while(p>=x)p=Pollard_Rho(x);
	    while(x%p==0)x/=p;
	    fac(x),fac(p);
	}
}

int main()
{
 	ios::sync_with_stdio(false);cin.tie(0);
    srand(time(0));
    ll T;cin>>T;
    while(T--)
    {
        ll n;cin>>n;
        PR::prime.clear();
        PR::fac(n);
        set<ll>::iterator it=PR::prime.end();
		it--;
		if((*it)!=n)cout<<(*it)<<endl;
		else cout<<"Prime"<<endl;
//		for(int x:PR::prime)cout<<x<<" ";cout<<endl;
    }
    return 0;
}
