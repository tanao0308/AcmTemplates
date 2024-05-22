//https://www.luogu.com.cn/problem/AT_arc017_1
//ģ��
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
    	  	if(v==n-1)break; // �õ�ƽ��ƽ���� n-1��ͨ�����ֲ���
    	  	v=v*v%n;
    	}
    	// ����ҵ��˷�ƽ��ƽ��������������޷���ǰ break; �����е� s == t
    	// ��� Fermat ���Բ����޷�ͨ������һֱ���е� s == t ǰ v ��������� -1
    	if(s==t)return 0;
  	}
  	return 1;
}

// bool check_prime(ll n){//�����ޱ���
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

