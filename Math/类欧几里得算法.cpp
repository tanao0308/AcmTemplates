#include <bits/stdc++.h>
#define ll long long
using namespace std;
//ll f(ll n,ll a,ll b,ll c)
//{
//	ll ac=a/c,bc=b/c;
//	ll m=(a*n+b)/c;
//	if(a==0)
//		return (n+1)*bc;
//	if(a>=c||b>=c)
//		return f(n,a%c,b%c,c)+n*(n+1)/2*ac+(n+1)*bc;
//	return n*m-f(m-1,c,c-b-1,a);
//}
namespace EL
{
	const ll MOD=998244353;
	ll i2=499122177,i6=166374059;
	struct data
	{
		data()
		{
			f=g=h=0;
		}
	  	ll f,g,h;
	};
	data calc(ll n,ll a,ll b,ll c)
	{
	  	ll ac=a/c,bc=b/c,m=(a*n+b)/c,n1=n+1,n21=n*2+1;
	  	data d;
	  	if(a==0)
		{
	    	d.f=bc*n1%MOD;
	    	d.g=bc*n%MOD*n1%MOD*i2%MOD;
	    	d.h=bc*bc%MOD*n1%MOD;
	    	return d;
	  	}
	  	if(a>=c||b>=c)
		{
	    	d.f=n*n1%MOD*i2%MOD*ac%MOD+bc*n1%MOD;
	    	d.g=ac*n%MOD*n1%MOD*n21%MOD*i6%MOD+bc*n%MOD*n1%MOD*i2%MOD;
	    	d.h=ac*ac%MOD*n%MOD*n1%MOD*n21%MOD*i6%MOD+bc*bc%MOD*n1%MOD+ac*bc%MOD*n%MOD*n1%MOD;
	    	d.f%=MOD,d.g%=MOD,d.h%=MOD;
		    data e=calc(n,a%c,b%c,c);  // µü´ú
		    d.h+=e.h+2*bc%MOD*e.f%MOD+2*ac%MOD*e.g%MOD;
		    d.g+=e.g,d.f+=e.f;
		    d.f%=MOD,d.g%=MOD,d.h%=MOD;
		    return d;
	  	}
		data e=calc(m-1,c,c-b-1,a);
		d.f=n*m%MOD-e.f,d.f=(d.f%MOD+MOD)%MOD;
		d.g=m*n%MOD*n1%MOD-e.h-e.f,d.g=(d.g*i2%MOD+MOD)%MOD;
		d.h=n*m%MOD*(m+1)%MOD-2*e.g-2*e.f-d.f;
		d.h=(d.h%MOD+MOD)%MOD;
		return d;
	}
}
int main()
{
 	ios::sync_with_stdio(false);cin.tie(0);
	ll T;cin>>T;
	while(T--)
	{
		ll n,a,b,c;
		cin>>n>>a>>b>>c;
    	EL::data ans=EL::calc(n, a, b, c);
    	cout<<ans.f<<" "<<ans.h<<" "<<ans.g<<endl;
  	}
  	return 0;
}
