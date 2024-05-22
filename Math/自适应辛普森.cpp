#include<bits/stdc++.h>
#define ll long long
#define mid ((l+r)/2)
#define inf0 1e-9
using namespace std;
namespace INT
{
	double a;
	double f(double x)
	{
		return pow(x,(a/x)-x);
	}
	double simpson(double l,double r)
	{
		return (r-l)*(f(l)+f(r)+4*f(mid))/6;
	}
	double asr(double l,double r,double eps,double ans)
	{
		double fl=simpson(l,mid),fr=simpson(mid,r);
		if(fabs(fl+fr-ans)<15*eps)return fl+fr+(fl+fr-ans)/15;
		return asr(l,mid,eps/2,fl)+asr(mid,r,eps/2,fr);
	}
	double calans(double l,double r)
	{
		return asr(l,r,inf0,simpson(l,r));
	}
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
	cin>>INT::a;
	if(INT::a<0)cout<<"orz"<<endl;
	else cout<<fixed<<setprecision(5)<<INT::calans(inf0,20)<<endl; 
	return 0;
}

