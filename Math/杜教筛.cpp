#include<bits/stdc++.h>
#define ll long long
#define mid ((l+r)>>1)
#define MAX_N 3000010
#define N 3000000
using namespace std;
namespace MU
{
	bool is[MAX_N];
	int mu[MAX_N];
	ll sum[MAX_N];
	vector<int>prime;
	void getmu(int n)
	{
	    mu[1]=is[1]=sum[1]=1;
	    for(int i=2;i<=n;++i)
	    {
	        if(!is[i])prime.push_back(i),mu[i]=-1;
	        for(int j=0;j<prime.size()&&i*prime[j]<=n;++j)
	        {
	            is[prime[j]*i]=1;
	            if(i%prime[j]==0)
	            {
	                mu[i*prime[j]]=0;
	                break;
	            }
	            mu[i*prime[j]]=mu[i]*mu[prime[j]];
	        }
	        sum[i]=sum[i-1]+mu[i];
	    }
	}
	map<ll,ll>S;
	ll getsum(ll n)
	{
		if(n<N)return sum[n];
		if(S[n])return S[n];
        ll ans=0;
        for(ll l=2,r;l<=n;l=r+1)
        {
            r=n/(n/l);
            ans+=(r-l+1)*getsum(n/l);
        }
        if(n<=N)sum[n]=1-ans;
        return S[n]=1-ans;
	}
}
namespace PHI
{
	bool is[MAX_N];
	int phi[MAX_N];
	ll sum[MAX_N];
	vector<int>prime;
	void getphi(int n)
	{
	    phi[1]=is[1]=sum[1]=1;
	    for(int i=2;i<=n;++i)
	    {
	        if(!is[i])prime.push_back(i),phi[i]=i-1;
	        for(int j=0;j<prime.size()&&i*prime[j]<=n;++j)
	        {
	            int p=prime[j];
	            is[p*i]=1;
	            if(i%p==0)
	            {
	                phi[p*i]=phi[i]*p;
	                break;
	            }
	            phi[p*i]=phi[p]*phi[i];
	        }
	        sum[i]=sum[i-1]+phi[i];
	    }
	}
	map<ll,ll>S;
	ll getsum(ll n)//∂≈ΩÃ…∏ 
	{
		if(n<=N)return sum[n];
		if(S[n])return S[n];
        ll ans=0;
        for(ll l=2,r;l<=n;l=r+1)
        {
            r=n/(n/l);
            ans+=(r-l+1)*getsum(n/l);
        }
        return S[n]=n*(n+1)/2-ans;
	}
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    int T;cin>>T;
    PHI::getphi(N);//init() 
    MU::getmu(N);//init()
	while(T--)
	{
		ll n;cin>>n;
		cout<<PHI::getsum(n)<<" "<<MU::getsum(n)<<endl;
	}
	return 0;
}
/*
mu[i]:			g=I0=[1,1,1,1...]
phi[i]:			g=I0=[1,1,1,1...]
id[i]*phi[i]:	g=I1=[1,2,3,4...]
id[i]^2*phi[i]: g=I2=[1,4,9,16...]
...
*/
