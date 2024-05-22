//https://www.luogu.com.cn/problem/AT_arc017_1
//模板
#include<bits/stdc++.h>
#define ll long long
#define LL __int128
#define mid ((l+r)>>1)
using namespace std;
ll power(ll a,ll b,ll MOD)
{
	ll ans=1;
	for(;b;b>>=1,a=a*a%MOD)
		if(b&1)ans=ans*a%MOD;
	return ans;
}
bool check_prime(ll n)
{
  	if(n<3||n%2==0)return n==2;
  	ll u=n-1,t=0;
  	while(u%2==0)u/=2,++t;
  	for(ll i=0;i<10;++i) 
  	{
    	ll a=rand()%(n-2)+2,v=power(a,u,n);
    	if(v==1)continue;
    	ll s;
    	for(s=0;s<t;++s) 
    	{
    	  	if(v==n-1)break; // 得到平凡平方根 n-1，通过此轮测试
    	  	v=v*v%n;
    	}
    	// 如果找到了非平凡平方根，则会由于无法提前 break; 而运行到 s == t
    	// 如果 Fermat 素性测试无法通过，则一直运行到 s == t 前 v 都不会等于 -1
    	if(s==t)return 0;
  	}
  	return 1;
}

// bool check_prime(ll n){//米勒罗宾法
// 	static const ll jp[]={2,3,5,7,11,13,17,19,23,29};
// 	if(n==1)return false;
// 	for (ll p:jp)if(n%p==0)return n==p;
// 	ll r=n-1,x,y;
// 	ll e=0;
// 	while(~r&1)r>>=1,++e;
// 	for(ll p:jp)
// 	{
// 		x=power(p,r,n);
// 		for (ll t=0;t<e&&x>1;++t)
// 		{
// 			y=(LL)x*x%n;
// 			if(y==1&&x!=n-1)return 0;
// 			x=y;
// 		}
// 		if (x!=1) return 0;
// 	}
// 	return 1;
// }
int main()
{
 	ios::sync_with_stdio(false);cin.tie(0);
	ll n;cin>>n;
	if(check_prime(n))cout<<"YES"<<endl;
	else cout<<"NO"<<endl;
	return 0;
}

