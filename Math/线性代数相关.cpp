#include<bits/stdc++.h>
#define ll long long
#define mid ((l+r)>>1)
#define MAX_N 200010
#define inf0 1e-9
#define MOD 998244353
using namespace std;
void print(vector<vector<double> >a)
{
    for(int i=0;i<a.size();++i)
    {
        for(int j=0;j<a[i].size();++j)
            cout<<a[i][j]<<" ";
        cout<<endl;
    }
}
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
	vector<vector<ll> >upper_triangular(vector<vector<ll> >a)//转化成上三角行列式 
	{
		ll xx=-1;
        for(int i=0;i<a.size();++i)
        {
            int p=i;
            for(int j=p+1;j<a.size();++j)
                if(a[j][i]>a[p][i])p=j;
            swap(a[i],a[p]);
            
            ll inv=power(a[i][i]);
            for(int j=0;j<a.size();++j)
                if(j!=i)for(int k=a[i].size()-1;k>=i;--k)
                    a[j][k]=(a[j][k]-a[j][i]*inv%MOD*a[i][k]%MOD+MOD)%MOD;
        }
	}
    vector<ll>linear_equations(vector<vector<ll> >a)
    {
        vector<ll>ans;
        //------
        for(int i=0;i<a.size();++i)
            ans.push_back(a[i][a[i].size()-1]*power(a[i][i])%MOD);
        return ans;
    }
    ll det(vector<vector<ll> >a)
    {
    	
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
    int n;cin>>n;
    vector<vector<double> >a(n);
    for(int i=0;i<n;++i)
        for(int j=0;j<=n;++j)
        {
            double x;
            cin>>x;
            a[i].push_back(x);
        }
    vector<double>ans=MAT_FLO::GaussElimination(a);
    if(!ans.size())cout<<"No Solution"<<endl;//多解或无解
    else
    {
        for(int i=0;i<ans.size();++i)
            cout<<fixed<<setprecision(2)<<ans[i]<<endl;
    }
    return 0;
}
