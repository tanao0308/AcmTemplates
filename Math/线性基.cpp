//贪心版，O(n*m) 
#include<bits/stdc++.h>
#define ll long long
#define mid ((l+r)>>1)
using namespace std;
namespace LB
{
	ll num[100];
	void insert(ll x)
	{
		for(ll i=60;i>=0;--i)
			if(x&(1ll<<i))
				if(num[i])x^=num[i];
				else{num[i]=x;return;}
	}
	bool check(ll x)
	{
		for(ll i=60;i>=0;--i)
			if(x&(1ll<<i))
				if(num[i])x^=num[i];
				else return 0;
		return 1;
	}
	ll qmax()
	{
		ll ans=0;
		for(ll i=60;i>=0;--i)
			if((ans&(1ll<<i))==0)
				ans^=num[i];
		return ans;
	}
	ll qmin()
	{
		for(ll i=0;i<=60;++i)
			if(num[i])return num[i];
		return 0;
	}
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    ll n,x;cin>>n;
    while(n--)
    	cin>>x,LB::insert(x);
    cout<<LB::qmax()<<endl;
	return 0;
}

/*
高斯消元法解异或方程 
线代版线性基，O(n*m^2) 
*/ 
/*
#include<bits/stdc++.h>
#define ll long long
#define mid ((l+r)>>1)
using namespace std;
template<typename T>
void prll(vector<vector<T> >a)
{
    for(ll i=0;i<a.size();++i)
    {
        for(ll j=0;j<a[i].size();++j)
            cout<<a[i][j]<<" ";
        cout<<endl;
    }
}
namespace LB //Linear basis
{
    vector<vector<ll> >upper_triangular(vector<vector<ll> >a)
    {
        ll xx=-1;//i,xx为主元 
        for(ll i=0;i<a.size();++i)
        {
        	ll p=-1;
        	while(1)
        	{
        		xx++;if(xx>=a[0].size())break;
        		for(ll j=i;j<a.size();++j)
        			if(a[j][xx])p=j;
        		if(p!=-1)break;
			}
			if(p==-1)return a;
            swap(a[i],a[p]);
            
            for(ll j=0;j<a.size();++j)
                if(j!=i&&a[j][xx])for(ll k=a[j].size()-1;k>=xx;--k)
                    a[j][k]^=a[i][k];
        }
        return a;
    }
	vector<ll>build(vector<ll>num)
	{
		vector<vector<ll> >a(num.size());
	    for(ll i=0;i<num.size();++i)
	    {
	    	ll x=num[i];
	    	for(ll j=0;j<60;++j,x>>=1)
	    		a[i].push_back(x&1);
	    	reverse(a[i].begin(),a[i].end());
		}
		a=upper_triangular(a);
		vector<ll>ans;
		for(ll i=0;i<a.size();++i)
		{
			ll t=0;
			for(ll j=0;j<a[i].size();++j)
				t=t*2+a[i][j];
			if(t)ans.push_back(t);
		}
		return ans;
	}
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    ll n;cin>>n;
    vector<ll>a(n);//n*50矩阵，化为上三角矩阵 
    for(ll i=0;i<n;++i)cin>>a[i];
    vector<ll>ans=LB::build(a);
    ll sum=0;
    for(ll i=0;i<ans.size();++i)sum^=ans[i];
    cout<<sum<<endl;
	return 0;
}
*/
