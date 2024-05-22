#include<bits/stdc++.h>
#define ll long long
#define mid ((l+r)>>1)
#define MAX_N 200010
#define inf0 1e-9
using namespace std;
template<typename T>
void print(vector<vector<T> >a)
{
    for(int i=0;i<a.size();++i)
    {
        for(int j=0;j<a[i].size();++j)
            cout<<a[i][j]<<" ";
        cout<<endl;
    }
}
ll MOD;
ll power(ll a,ll b=MOD-2)
{
	ll ans=1;
	while(b)
	{
		if(b&1)ans=ans*a%MOD;
		a=a*a%MOD;
		b>>=1;
	}
	return ans;
}
namespace MAT_INT 
{
    vector<ll>GaussElimination(vector<vector<ll> >a)
    {
        vector<ll>ans;
        for(int i=0;i<a.size();++i)
        {
            int p=i;
            for(int j=p+1;j<a.size();++j)
                if(a[j][i]>a[p][i])p=j;
            swap(a[i],a[p]);
            
            if(!a[i][i])return ans;//多解或无解返回空vector
            
            ll inv=power(a[i][i]);
            for(int j=0;j<a.size();++j)
                if(j!=i)for(int k=a[i].size()-1;k>=i;--k)
                    a[j][k]=(a[j][k]-a[j][i]*inv%MOD*a[i][k]%MOD+MOD)%MOD;
        }
        for(int i=0;i<a.size();++i)
            ans.push_back(a[i][a[i].size()-1]*power(a[i][i])%MOD);
        return ans;
    }
    ll det(vector<vector<ll> >a)
    {
    	bool flag=0;int n=a.size();
        for(int i=0;i<n;++i)
        {
            int p=i;
            for(int j=p+1;j<n;++j)
                if(a[j][i]>a[p][i])p=j;
            if(p!=i)swap(a[i],a[p]),flag^=1;
            
            ll inv=power(a[i][i]);
            for(int j=0;j<n;++j)
                if(j!=i)for(int k=n-1;k>=i;--k)
                    a[j][k]=(a[j][k]-a[j][i]*inv%MOD*a[i][k]%MOD+MOD)%MOD;
        }
        ll ans=1;
        for(int i=0;i<n;++i)ans=ans*a[i][i]%MOD;
        return (ans*(flag?-1:1)+MOD)%MOD;
	}
}
namespace MAT_FLO
{
    vector<double>GaussElimination(vector<vector<double> >a)
    {
        vector<double>ans;
        for(int i=0;i<a.size();++i)
        {
            int p=i;
            for(int j=p+1;j<a.size();++j)
                if(a[j][i]>a[p][i])p=j;
            swap(a[i],a[p]);
            
            if(abs(a[i][i])<inf0)return ans;//多解或无解返回空vector
            
            for(int j=0;j<a.size();++j)
                if(j!=i)for(int k=a[i].size()-1;k>=i;--k)
                    a[j][k]-=a[j][i]/a[i][i]*a[i][k];
        }
        for(int i=0;i<a.size();++i)
            ans.push_back(a[i][a[i].size()-1]/a[i][i]);
        return ans;
    }
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    int n;cin>>n>>MOD;
    vector<vector<ll> >a(n);
    for(int i=0;i<n;++i)
        for(int j=0;j<n;++j)
        {
            ll x;cin>>x;
            a[i].push_back(x);
        }
//    print(a);return 1;
    cout<<MAT_INT::det(a)<<endl;
    return 0;
}
