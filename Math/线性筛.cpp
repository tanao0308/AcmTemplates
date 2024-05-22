#include<bits/stdc++.h>
#define MAX_N 100010
#define ll long long
#define mid ((l+r)>>1)
using namespace std;
namespace PRI//线性筛素数 
{
	vector<int>prime;
	bool is[MAX_N];
	void getpri(int n)
	{//算法原理：每个整数只被它最小的质因数筛掉 
	    is[1]=1;
	    for(int i=2;i<=n;++i)
	    {
	        if(!is[i])prime.push_back(i);
	        for(int j=0;j<prime.size()&&i*prime[j]<=n;++j)
	        {
	            is[i*prime[j]]=1;//这里 i*prime[j]的最小质因数为prime[j] 
	            if(i%prime[j]==0)break;
				//如果i是prime[j]的倍数，那之后的i*prime[k](k>j)的最小质因数都为prime[j],不应该用prime[k]去筛 
	        }
	    }
	}
}
namespace D//线性筛约数个数 
{
	bool is[MAX_N];
	int d[MAX_N],num[MAX_N];
	vector<int>prime;
	void getd(int n)
	{
	    d[1]=is[1]=1,num[1]=0;
	    for(int i=2;i<=n;++i)
	    {
	        if(!is[i])prime.push_back(i),d[i]=2,num[i]=1;
	        for(int j=0;j<prime.size()&&i*prime[j]<=n;++j)
	        {
	            is[prime[j]*i]=1;
	            if(i%prime[j]==0)
	            {
	                d[i*prime[j]]=d[i]/(num[i]+1)*(num[i]+2);
	            	num[i*prime[j]]=num[i]+1;
	                break;
	            }
	            d[i*prime[j]]=d[i]*d[prime[j]];
	            num[i*prime[j]]=1;
	        }
	    }
	}
}
namespace PHI//线性筛欧拉函数 
{
	bool is[MAX_N];
	int phi[MAX_N];
	vector<int>prime;
	void getphi(int n)
	{//每个数的欧拉函数只被它最小的质因数计算出来，原理同线性筛素数 
	    phi[1]=is[1]=1;
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
	    }
	}
}
namespace MU//线性筛莫比乌斯函数 
{
	bool is[MAX_N];
	int mu[MAX_N];
	vector<int>prime;
	void getmu(int n)
	{
	    mu[1]=is[1]=1;
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
	    }
	}
}
#define MOD 998244353
namespace INV//线性求逆元 
{
	ll inv[MAX_N];
	void getinv(int n)
	{
	    inv[1]=1;
	    for(int i=2;i<=n;++i)
	        inv[i]=(MOD-MOD/i)*inv[MOD%i]%MOD;
	}
}
int main()
{
    int n;cin>>n;
    PRI::getpri(n);
    for(int i=0;i<PRI::prime.size();++i)cout<<PRI::prime[i]<<" ";cout<<endl;
    D::getd(n);
    for(int i=1;i<=n;++i)cout<<D::d[i]<<" ";cout<<endl;
    PHI::getphi(n);
    for(int i=1;i<=n;++i)cout<<PHI::phi[i]<<" ";cout<<endl;
    MU::getmu(n);
    for(int i=1;i<=n;++i)cout<<MU::mu[i]<<" ";cout<<endl;
    INV::getinv(n);
    for(int i=1;i<=n;++i)cout<<INV::inv[i]<<" ";cout<<endl;
    return 0;
}
