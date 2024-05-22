#include<bits/stdc++.h>
#define ll long long
#define mid ((l+r)>>1)
#define MAX_N 200010
using namespace std;
const int MOD=1000000007;
void print(vector<vector<ll> >a)
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
namespace MAT
{
    vector<vector<ll> >inversematrix(vector<vector<ll> >a)
    {
        vector<ll>b(a.size());
        for(int i=0;i<a.size();++i)
            b[i]=1,a[i].insert(a[i].end(),b.begin(),b.end()),b[i]=0;
//        print(a);exit(1);
        for(int i=0;i<a.size();++i)
        {
            int p=i;
            for(int j=p;j<a.size();++j)
                if(a[j][i])
                {
                    p=j;
                    break;
                }
            if(i!=p)swap(a[i],a[p]);
            for(int j=a[i].size(),x=power(a[i][i]);j>=i;--j)
                a[i][j]=a[i][j]*x%MOD;

            if(a[i][i]==0)return vector<vector<ll> >(0);//????????vector

            for(int j=0;j<a.size();++j)
                if(j!=i)for(int k=a[i].size()-1;k>=i;--k)
                    a[j][k]=(a[j][k]-a[j][i]*a[i][k]%MOD+MOD)%MOD;
//            print(a);cout<<endl;
        }
        vector<vector<ll> >ans(a.size());
        for(int i=0;i<a.size();++i)
            for(int j=0;j<a.size();++j)
                ans[i].push_back(a[i][j+a.size()]);
        return ans;
    }
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    int n;cin>>n;
    vector<vector<ll> >a(n);
    for(int i=0;i<n;++i)
        for(int j=0;j<n;++j)
        {
            ll x;
            cin>>x;
            a[i].push_back(x);
        }
    vector<vector<ll> >ans=MAT::inversematrix(a);
    if(ans.size())print(ans);
    else cout<<"No Solution"<<endl;
    return 0;
}
